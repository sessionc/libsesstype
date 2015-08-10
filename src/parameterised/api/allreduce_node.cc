#include <sesstype/parameterised/msg.h>
#include <sesstype/parameterised/node.h>
#include <sesstype/parameterised/node/allreduce.h>

namespace sesstype {
namespace parameterised {

st_node *st_mk_allreduce_node_init()
{
    return new AllReduceNode();
}

st_node *st_mk_allreduce_node(st_msg *msg)
{
    return new AllReduceNode(msg);
}

st_node *st_allreduce_node_set_msgsig(st_node *const node, st_msg *msg)
{
    if (auto allreduce = dynamic_cast<AllReduceNode *>(node)) {
        allreduce->set_msg(msg);
    }
    return node;
}

st_msg *st_allreduce_node_get_msgsig(st_node *const node)
{
    if (auto allreduce = dynamic_cast<AllReduceNode *>(node)) {
        return allreduce->msg();
    }
    return nullptr;
}

} // namespace parameterised
} // namespace sesstype

