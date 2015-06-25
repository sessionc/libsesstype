/**
 * \file utils/parameterised/projection.cc
 * \brief Endpoint projection.
 */
#include <sesstype/parameterised/node.h>
#include <sesstype/parameterised/role.h>
#include <sesstype/utils.h>

namespace sesstype {
namespace utils {

void Projection::visit(parameterised::InteractionNode *node)
{
    // TODO
}

void Projection::visit(parameterised::AllReduceNode *node)
{
    return;
}

void Projection::visit(parameterised::ForNode *node)
{
    for (auto it=node->child_begin(); it!=node->child_end(); it++) {
        (*it)->accept(*this);
    }
}

void Projection::visit(parameterised::OneofNode *node)
{
  // TODO
}

void Projection::visit(parameterised::IfNode *node)
{
    for (auto it=node->child_begin(); it!=node->child_end(); it++) {
        (*it)->accept(*this);
    }
}

} // namespace utils
} // namespace sesstype
