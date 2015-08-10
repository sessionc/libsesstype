#include <sesstype/parameterised/cond.h>
#include <sesstype/parameterised/node.h>
#include <sesstype/parameterised/node/if.h>

namespace sesstype {
namespace parameterised {

st_node *st_mk_if_node(st_cond *cond)
{
    return new IfNode(cond);
}

} // namespace parameterised
} // namespace sesstype
