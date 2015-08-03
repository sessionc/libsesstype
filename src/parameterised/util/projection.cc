/**
 * \file parameterised/util/projection.cc
 * \brief Endpoint projection.
 */
#include <algorithm>

#include <sesstype/parameterised/node.h>
#include <sesstype/parameterised/role.h>
#include <sesstype/parameterised/util.h>

namespace sesstype {
namespace parameterised {
namespace util {

Projection::Projection(Role *role)
{
}

sesstype::Node *Projection::get_root()
{
    return stack_.top();
}

void Projection::visit(Node *node)
{
    return;
}

void Projection::visit(BlockNode *node)
{
    for (auto it=node->child_begin(); it!=node->child_end(); it++) {
        (*it)->accept(*this);
    }
}

void Projection::visit(InteractionNode *node)
{
    // TODO
}

void Projection::visit(RecurNode *node)
{
    RecurNode *new_node = new RecurNode(node->label());
    stack_.push(new_node);
    node->BlockNode::accept(*this);
    stack_.pop();
    dynamic_cast<BlockNode *>(stack_.top())->append_child(new_node);
}

void Projection::visit(ContinueNode *node)
{
    ContinueNode *new_node = new ContinueNode(node->label());
    dynamic_cast<BlockNode *>(stack_.top())->append_child(new_node);
}

void Projection::visit(ChoiceNode *node)
{
    ChoiceNode *new_node = node->clone();
    stack_.push(new_node);
    if (project_role_->matches(node->at())) {
        // Choice sender
    }
    node->BlockNode::accept(*this);
    stack_.pop();
    dynamic_cast<BlockNode *>(stack_.top())->append_child(new_node);
}

void Projection::visit(ParNode *node)
{
    ParNode *new_node = new ParNode();
    stack_.push(new_node);
    node->BlockNode::accept(*this);
    stack_.pop();
    dynamic_cast<BlockNode *>(stack_.top())->append_child(new_node);
}

void Projection::visit(NestedNode *node)
{
    for (auto it=node->rolearg_begin(); it!=node->rolearg_end(); it++) {
        if ((*it)->matches(project_role_)) {
            dynamic_cast<BlockNode *>(stack_.top())->append_child(node->clone());
            break;
        }
    }
}

void Projection::visit(InterruptibleNode *node)
{
    InterruptibleNode *new_node = node->clone();

    stack_.push(new_node);
    node->BlockNode::accept(*this);
    stack_.pop();

    dynamic_cast<BlockNode *>(stack_.top())->append_child(new_node);
}

void Projection::visit(AllReduceNode *node)
{
    return;
}

void Projection::visit(ForNode *node)
{
    for (auto it=node->child_begin(); it!=node->child_end(); it++) {
        (*it)->accept(*this);
    }
}

void Projection::visit(OneofNode *node)
{
  // TODO
}

void Projection::visit(IfNode *node)
{
    for (auto it=node->child_begin(); it!=node->child_end(); it++) {
        (*it)->accept(*this);
    }
}

} // namespace util
} // namespace parameterised
} // namespace sesstype
