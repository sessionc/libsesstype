#include <iostream>

#include <sesstype/node.h>
#include <sesstype/node/par.h>

namespace sesstype {

st_node *st_mk_par_node_init()
{
    return new ParNode();
}

st_node *st_par_node_add_parallel(st_node *const node, st_node *par_blk)
{
    if (auto par = dynamic_cast<ParNode *>(node)) {
        par->append_child(par_blk);
    }
    return node;
}

} // namespace sesstype
