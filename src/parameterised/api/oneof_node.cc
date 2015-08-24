#include <sesstype/parameterised/node.h>
#include <sesstype/parameterised/node/oneof.h>
#include <sesstype/parameterised/role.h>

namespace sesstype {
namespace parameterised {

st_node *st_mk_oneof_node(st_param_role *selector_role, unsigned int dimen)
{
    return new OneofNode(selector_role, dimen);
}

} // namespace parameterised
} // namespace sesstype
