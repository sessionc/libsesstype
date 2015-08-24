#ifndef SESSTYPE__UTIL__PROJECT_H__
#define SESSTYPE__UTIL__PROJECT_H__

#ifdef __cplusplus
#include <stack>
#endif

#include "sesstype/role.h"
#include "sesstype/node.h"
#include "sesstype/node/block.h"
#include "sesstype/node/interaction.h"
#include "sesstype/node/choice.h"
#include "sesstype/node/recur.h"
#include "sesstype/node/continue.h"
#include "sesstype/node/par.h"
#include "sesstype/node/nested.h"
#include "sesstype/node/interruptible.h"
#include "sesstype/util/node_visitor.h"

#ifdef __cplusplus
namespace sesstype {
namespace util {
#endif

#ifdef __cplusplus
/**
 * \brief Endpoint projection.
 */
class ProjectionVisitor : public NodeVisitor {
    Role *endpoint_;
    std::stack<Node *> stack_;

  public:
    ProjectionVisitor(Role *endpoint) : endpoint_(endpoint), stack_()
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
        /// Note that we are not adding a new root node here,
        /// because the parent is addeded by one of below:
        ///
        /// 1. Subclass of BlockNode
        /// 2. Constructor if this is the root Node
        ///    (the only place when BlockNode exists as BlockNode)
        for (auto it=node->child_begin(); it!=node->child_end(); it++) {
            (*it)->accept(*this);
        }
    }

    void visit(InteractionNode *node) override
    {
        auto *parent = dynamic_cast<BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *>(stack_.top());
        InteractionNode *projected_node;

        if (node->sndr()->matches(endpoint_)) {
            projected_node = node->clone();
            projected_node->remove_sndr();
            parent->append_child(projected_node);
            return;
        }
        for (auto it=node->rcvr_begin(); it!=node->rcvr_end(); it++) {
            if (*it && (*it)->matches(endpoint_)) {
                projected_node = node->clone();
                projected_node->remove_rcvrs();
                parent->append_child(projected_node);
                return;
            }
        }

        // Remove this node because is does not match from/to
    }

    void visit(ChoiceNode *node)
    {
        auto *projected_node = new ChoiceNode(node->at());

        stack_.push(projected_node);
        if (endpoint_->matches(projected_node->at())) {
            // Choice sender
        }
        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
        stack_.pop();

        dynamic_cast<BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *>(stack_.top())->append_child(projected_node);
    }

    void visit(RecurNode *node) override
    {
        auto *projected_node = new RecurNode(node->label());

        stack_.push(projected_node);
        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
        stack_.pop();

        dynamic_cast<BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *>(stack_.top())->append_child(projected_node);
    }

    void visit(ContinueNode *node) override
    {
        auto *projected_node = new ContinueNode(node->label());
        dynamic_cast<BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *>(stack_.top())->append_child(projected_node);
    }

    void visit(ParNode *node)
    {
        auto *projected_node = new ParNode();

        stack_.push(projected_node);
        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
        stack_.pop();

        dynamic_cast<BlockNode *>(stack_.top())->append_child(projected_node);
    }

    void visit(NestedNode *node)
    {
        // Only include nested node if role arg matches.
        for (auto it=node->rolearg_begin(); it!=node->rolearg_end(); it++) {
            if ((*it)->matches(endpoint_)) {
                dynamic_cast<BlockNode *>(stack_.top())->append_child(node->clone());
                break;
            }
        }
    }

    void visit(InterruptibleNode *node)
    {
        auto *new_node = node->clone();

        // TODO only retain interrupts relevant to endpoint role?

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

#endif//SESSTYPE__UTIL__PROJECT_H__
