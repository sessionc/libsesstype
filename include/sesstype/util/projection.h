#ifndef SESSTYPE__UTIL__PROJECTION_H__
#define SESSTYPE__UTIL__PROJECTION_H__

#ifdef __cplusplus
#include <stack>
#endif

#include "sesstype/role.h"
#include "sesstype/node.h"
#include "sesstype/util/node_visitor.h"

#ifdef __cplusplus
namespace sesstype {
namespace util {
#endif

#ifdef __cplusplus
/**
 * \brief Endpoint projection.
 */
class Projection : public NodeVisitor {
    Role *endpoint_;
    std::stack<Node *> stack_;

  public:
    Projection(Role *role) : endpoint_(role), stack_()
    {
        stack_.push(new BlockNode());
    }

    Node *get_root()
    {
        return stack_.top();
    }

    void visit(Node *node) override
    {
       // Nothing.
    }

    void visit(BlockNode *node) override
    {
        for (auto it=node->child_begin(); it!=node->child_end(); it++) {
            (*it)->accept(*this);
        }
    }

    void visit(InteractionNode *node) override
    {
        BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *parent = dynamic_cast<BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *>(stack_.top());
        InteractionNode *inode;
        if (node->sndr()->matches(endpoint_)) {
            inode = node->clone();
            inode->remove_sndr();
            parent->append_child(inode);
            return;
        }
        for (auto it=node->rcvr_begin(); it!=node->rcvr_end(); it++) {
            if (*it && (*it)->matches(endpoint_)) {
                inode = node->clone();
                inode->clear_rcvrs();
                parent->append_child(inode);
                return;
            }
        }

        // Remove this node because is does not match from/to
    }

    void visit(ChoiceNode *node)
    {
        ChoiceNode *new_node = new ChoiceNode(node->at());
        stack_.push(new_node);
        if (endpoint_->matches(node->at())) {
            // Choice sender
        }
        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
        stack_.pop();
        dynamic_cast<BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *>(stack_.top())->append_child(new_node);
    }

    void visit(RecurNode *node) override
    {
        RecurNode *new_node = new RecurNode(node->label());
        stack_.push(new_node);
        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
        stack_.pop();
        dynamic_cast<BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *>(stack_.top())->append_child(new_node);
    }

    void visit(ContinueNode *node) override
    {
        ContinueNode *new_node = new ContinueNode(node->label());
        dynamic_cast<BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *>(stack_.top())->append_child(new_node);
    }

    void visit(ParNode *node)
    {
        ParNode *new_node = new ParNode();
        stack_.push(new_node);
        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
        stack_.pop();
        dynamic_cast<BlockNode *>(stack_.top())->append_child(new_node);
    }

    void visit(NestedNode *node)
    {
        for (auto it=node->rolearg_begin(); it!=node->rolearg_end(); it++) {
            if ((*it)->matches(endpoint_)) {
                dynamic_cast<BlockNode *>(stack_.top())->append_child(node->clone());
                break;
            }
        }
    }

    void visit(InterruptibleNode *node)
    {
        InterruptibleNode *new_node = node->clone();

        stack_.push(new_node);
        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
        stack_.pop();

        dynamic_cast<BlockNode *>(stack_.top())->append_child(new_node);
    }
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace sesstype
#endif

#endif//SESSTYPE__UTIL__PROJECTION_H__
