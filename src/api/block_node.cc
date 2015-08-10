#include <sesstype/node.h>
#include <sesstype/node/block.h>

namespace sesstype {

st_node *st_node_append_child(st_node *const parent, st_node *child)
{
    if (auto blknode = dynamic_cast<BlockNode *>(parent)) {
        blknode->append_child(child);
    }
    return parent;
}

unsigned int st_node_num_children(st_node *const parent)
{
    if (auto blknode = dynamic_cast<BlockNode *>(parent)) {
        return blknode->num_children();
    }
    return 0;
}

st_node *st_node_get_child(st_node *const parent, unsigned int index)
{
    if (auto blknode = dynamic_cast<BlockNode *>(parent)) {
        return blknode->child(index);
    }
    return nullptr;
}

} // namespace sesstype
