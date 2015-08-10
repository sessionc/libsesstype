#include <sesstype/node.h>
#include <sesstype/node/recur.h>

namespace sesstype {

st_node *st_mk_recur_node(char *label)
{
    return new RecurNode(label);
}

st_node *st_recur_node_set_label(st_node *const node, char *label)
{
    if (auto recur = dynamic_cast<RecurNode *>(node)) {
        recur->set_label(label);
    }
    return node;
}
const char *st_recur_node_get_label(st_node *const node)
{
    if (auto recur = dynamic_cast<RecurNode *>(node)) {
        return recur->label().c_str();
    }
    return nullptr;
}

} // namespace sesstype
