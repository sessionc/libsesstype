#include <sesstype/parameterised/node.h>
#include <sesstype/parameterised/util/print.h>

namespace sesstype {
namespace parameterised {

void st_param_node_print(st_param_node *node)
{
    util::Print p;
    node->accept(p);
}

} // namespace parameterised
} // namespace sesstype
