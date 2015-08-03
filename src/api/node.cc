#include <iostream>

#include <sesstype/role.h>
#include <sesstype/node.h>
#include <sesstype/node/block.h>

namespace sesstype {

void st_node_append_child(st_node *parent, st_node *child)
{
    if (BlockNode *node = dynamic_cast<BlockNode *>(parent)) {
        node->append_child(child);
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": parent is not a Block.\n";
    }
}

unsigned int st_node_num_children(st_node *parent)
{
    if (BlockNode *node = dynamic_cast<BlockNode *>(parent)) {
        return node->num_children();
    } else {
        return 0;
    }
}

st_node *st_node_get_child(st_node *parent, unsigned int index)
{
    if (BlockNode *node = dynamic_cast<BlockNode *>(parent)) {
        return node->child(index);
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": parent is not a Block and has no children.\n";
        return nullptr;
    }
}

void st_node_free(st_node *node)
{
    delete node;
}

} // namespace sesstype
