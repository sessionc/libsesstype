#include <sesstype/parameterised/msg.h>
#include <sesstype/parameterised/node/allreduce.h>

namespace sesstype {
namespace parameterised {

AllReduceNode::AllReduceNode()
    : Node(ST_NODE_ALLREDUCE),
      msgsig_(new MsgSig(""))
{
}

AllReduceNode::AllReduceNode(MsgSig *msgsig)
    : Node(ST_NODE_ALLREDUCE),
      msgsig_(msgsig)
{
}

AllReduceNode::AllReduceNode(const AllReduceNode &node)
    : Node(ST_NODE_ALLREDUCE),
      msgsig_(node.msgsig_)
{
}

AllReduceNode::~AllReduceNode()
{
}

AllReduceNode *AllReduceNode::clone() const
{
    return new AllReduceNode(*this);
}

MsgSig* AllReduceNode::msgsig() const
{
    return msgsig_;
}

void AllReduceNode::set_msgsig(MsgSig *msgsig)
{
    msgsig_ = msgsig->clone();
}

} // namespace parameterised
} // namespace sesstype
