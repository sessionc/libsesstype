#include <iostream>

#include <sesstype/parameterised/expr.h>
#include <sesstype/parameterised/node.h>
#include <sesstype/parameterised/node/for.h>

namespace sesstype {
namespace parameterised {

ForNode::ForNode(RngExpr *bindexpr)
    : BlockNode(ST_NODE_FOR),
      bindexpr_(bindexpr)
{
}

ForNode::ForNode(const ForNode &node)
    : BlockNode(node),
      bindexpr_(node.bindexpr_)
{
}

ForNode::~ForNode()
{
    delete bindexpr_;
}

ForNode *ForNode::clone() const
{
    return new ForNode(*this);
}

void ForNode::set_bindexpr(RngExpr *bindexpr)
{
    delete bindexpr_;
    bindexpr_ = bindexpr;
}

RngExpr *ForNode::bindexpr() const
{
    if (bindexpr_ == NULL) {
        std::cerr << "Warning: bind_expr is NULL.\n";
    }
    return bindexpr_;
}

} // namespace parameterised
} // namespace sesstype
