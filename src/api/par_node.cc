#include <iostream>

#include <sesstype/node.h>
#include <sesstype/node/par.h>

namespace sesstype {

st_node *st_mk_par_node_init()
{
    return new ParNode();
}

st_node *st_par_node_add_parallel(st_node *node, st_node *par_blk)
{
    if (ParNode *par = dynamic_cast<ParNode *>(node)) {
        par->append_child(par_blk);
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node not a Par.\n";
    }
    return node;
}

} // namespace sesstype
