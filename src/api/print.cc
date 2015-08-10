#include <sesstype/node.h>
#include <sesstype/util/print.h>

namespace sesstype {

void st_node_print(st_node *node)
{
    sesstype::util::Print p;
    node->accept(p);
}

} // namespace util
