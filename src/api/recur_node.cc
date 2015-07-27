#include <iostream>

#include <sesstype/node.h>
#include <sesstype/node/recur.h>

namespace sesstype {

st_node *st_mk_recur_node(char *label)
{
    return new RecurNode(label);
}

st_node *st_recur_node_set_label(st_node *node, char *label)
{
    if (RecurNode *recur = dynamic_cast<RecurNode *>(node)) {
        recur->set_label(label);
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node is not a Recur.\n";
    }
    return node;
}
const char *st_recur_node_get_label(st_node *node)
{
    if (RecurNode *recur = dynamic_cast<RecurNode *>(node)) {
        return recur->label().c_str();
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node is not a Recur.\n";
        return nullptr;
    }
}

} // namespace sesstype
