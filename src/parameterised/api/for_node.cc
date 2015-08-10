#include <sesstype/parameterised/expr/rng.h>
#include <sesstype/parameterised/node.h>
#include <sesstype/parameterised/node/for.h>

namespace sesstype {
namespace parameterised {

st_node *st_mk_for_node(st_rng_expr *bindexpr)
{
    return new ForNode(bindexpr);
}

st_rng_expr *st_for_node_get_bindexpr(st_node *const node)
{
    if (auto fornode = dynamic_cast<ForNode *>(node)) {
        return fornode->bindexpr();
    }
    return nullptr;
}

st_node *st_for_node_set_bindexpr(st_node *const node, st_rng_expr *bindexpr)
{
    if (auto fornode = dynamic_cast<ForNode *>(node)) {
        fornode->set_bindexpr(bindexpr);
    }
    return node;
}

} // namespace parameterised
} // namespace sesstype
