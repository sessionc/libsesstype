/**
 * \file utils/projection.cc
 * \brief Endpoint projection.
 */
#include <sesstype/node.h>
#include <sesstype/role.h>
#include <sesstype/utils.h>

namespace sesstype {
namespace utils {

Projection::Projection(Role *role) : project_role_(role)
{
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
    node->BlockNode::accept(*this);
}

void Projection::visit(ContinueNode *node)
{
    return;
}

void Projection::visit(ChoiceNode *node)
{
    if (project_role_->matches(node->at())) {
        // Choice sender
    }
    node->BlockNode::accept(*this);
}

} // namespace utils
} // namespace sesstype
