#include <iostream>

#include <sesstype/node.h>
#include <sesstype/node/continue.h>

namespace sesstype {

st_node *st_mk_continue_node(char *label)
{
    return new ContinueNode(label);
}

st_node *st_continue_node_set_label(st_node *node, char *label)
{
    if (ContinueNode *cont = dynamic_cast<ContinueNode *>(node)) {
        cont->set_label(label);
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node is not a Continue.\n";
    }
    return node;
}

const char *st_continue_node_get_label(st_node *node)
{
    if (ContinueNode *cont = dynamic_cast<ContinueNode *>(node)) {
        return cont->label().c_str();
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node is not a Continue.\n";
        return nullptr;
    }
}

} // namespace sesstype
