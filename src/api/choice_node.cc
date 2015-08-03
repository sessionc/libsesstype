#include <iostream>

#include <sesstype/role.h>
#include <sesstype/node.h>
#include <sesstype/node/choice.h>

namespace sesstype {

st_node *st_mk_choice_node_init()
{
    return new ChoiceNode();
}

st_node *st_mk_choice_node(st_role *at)
{
    return new ChoiceNode(at);
}

Role *st_choice_node_get_at(st_node *node)
{
    if (ChoiceNode *choice = dynamic_cast<ChoiceNode *>(node)) {
        return choice->at();
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node not a Choice.\n";
        return nullptr;
    }
}
st_node *st_choice_node_set_at(st_node *node, st_role *at)
{
    if (ChoiceNode *choice = dynamic_cast<ChoiceNode *>(node)) {
        choice->set_at(at);
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node not a Choice.\n";
    }
    return node;
}

} // namespace sesstype
