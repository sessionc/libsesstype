#include <sesstype/parameterised/expr.h>
#include <sesstype/parameterised/node.h>
#include <sesstype/parameterised/role.h>
#include <sesstype/parameterised/node/oneof.h>

namespace sesstype {
namespace parameterised {

OneofNode::OneofNode(Role *selector, unsigned int dimen)
    : BlockNode(ST_NODE_ONEOF),
      selector_role_(selector),
      selector_dimen_(dimen),
      range_(),
      var_(),
      unordered_(false),
      repeat_(false)
{
}

OneofNode::OneofNode(const OneofNode &node)
    : BlockNode(node),
      selector_role_(node.selector_role_),
      selector_dimen_(node.selector_dimen_),
      range_(),
      var_(),
      unordered_(false),
      repeat_(false)
{
}

OneofNode::~OneofNode()
{
}

OneofNode *OneofNode::clone() const
{
    return new OneofNode(*this);
}

Role *OneofNode::selector_role() const
{
    return selector_role_;
}

unsigned int OneofNode::selector_dimen() const
{
    return selector_dimen_;
}

void OneofNode::set_var(std::string var)
{
    var_ = var;
}

std::string OneofNode::var() const
{
    return var_;
}

void OneofNode::set_repeat(bool repeat)
{
    repeat_ = repeat;
}

bool OneofNode::is_repeat() const
{
    return repeat_;
}

void OneofNode::set_range(RngExpr *range)
{
    range_ = range;
}

RngExpr *OneofNode::range() const
{
    return range_;
}

void OneofNode::set_selector(Role *selector, unsigned int dimen)
{
    selector_role_ = selector;
    selector_dimen_ = dimen;
}

void OneofNode::set_unordered(bool unordered)
{
    unordered_ = unordered;
}

bool OneofNode::is_unordered() const
{
    return unordered_;
}

} // namespace parameterised
} // namespace sesstype
