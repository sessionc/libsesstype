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

st_role *st_choice_node_get_at(st_node *const node)
{
    if (ChoiceNode *choice = dynamic_cast<ChoiceNode *>(node)) {
        return choice->at();
    }
    return nullptr;
}

st_node *st_choice_node_set_at(st_node *const node, st_role *at)
{
    if (auto choicenode = dynamic_cast<ChoiceNode *>(node)) {
        choicenode->set_at(at);
    }
    return node;
}

} // namespace sesstype
