#include <iostream>

#include <sesstype/role.h>
#include <sesstype/node.h>
#include <sesstype/node/block.h>

namespace sesstype {

void st_node_free(st_node *node)
{
    delete node;
}

} // namespace sesstype
