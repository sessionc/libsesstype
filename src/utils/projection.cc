/**
 * \file utils/projection.cc
 * \brief Endpoint projection.
 */
#include <algorithm>
#include <iostream>

#include <sesstype/node.h>
#include <sesstype/role.h>
#include <sesstype/utils.h>

namespace sesstype {
namespace utils {

Projection::Projection(Role *role)
    : project_role_(role), stack_()
{
    stack_.push(new BlockNode()); // Root.
}

Node *Projection::get_root()
{
    return stack_.top();
}

void Projection::visit(BlockNode *node)
{
    for (auto it=node->child_begin(); it!=node->child_end(); it++) {
        (*it)->accept(*this);
    }
}

void Projection::visit(InteractionNode *node)
{
    BlockNode *parent = dynamic_cast<BlockNode *>(stack_.top());
    InteractionNode *inode;
    if (node->from()->matches(project_role_)) {
        inode = node->clone();
        inode->remove_from();
        parent->append_child(inode);
        return;
    }
    for (auto it=node->to_begin(); it!=node->to_end(); it++) {
        if (*it && (*it)->matches(project_role_)) {
            inode = node->clone();
            inode->remove_tos();
            parent->append_child(inode);
            return;
        }
    }

    // Remove this node because is does not match from/to
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
    ChoiceNode *new_node = new ChoiceNode(node->at());
    stack_.push(new_node); // Enter Choice scope
    if (project_role_->matches(node->at())) {
        // Choice sender
    }
    node->BlockNode::accept(*this);
    stack_.pop(); // Exit Recur scope
    dynamic_cast<BlockNode *>(stack_.top())->append_child(new_node);
}

} // namespace utils
} // namespace sesstype
