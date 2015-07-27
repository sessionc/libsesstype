#include <sesstype/node/interaction.h>
#include <sesstype/parameterised/cond.h>
#include <sesstype/parameterised/node.h>
#include <sesstype/parameterised/node/interaction.h>

namespace sesstype {
namespace parameterised {

InteractionNode::InteractionNode()
    : sesstype::InteractionNode(),
      msgcond_(nullptr)
{
}

InteractionNode::InteractionNode(MsgSig *msgsig)
    : sesstype::InteractionNode(msgsig),
      msgcond_(nullptr)
{
}

InteractionNode::InteractionNode(const sesstype::InteractionNode &node)
    : sesstype::InteractionNode(node),
      msgcond_(nullptr)
{
}

InteractionNode::InteractionNode(const InteractionNode &node)
    : sesstype::InteractionNode(node),
      msgcond_(node.msgcond_ ? node.msgcond_->clone() : nullptr)
{
}

InteractionNode::~InteractionNode()
{
    delete msgcond_;
}

InteractionNode *InteractionNode::clone() const
{
    return new InteractionNode(*this);
}

MsgCond *InteractionNode::cond() const
{
    return msgcond_;
}

void InteractionNode::set_cond(MsgCond *cond)
{
    // Note: only possible for send/receive.
    msgcond_ = cond->clone();
}

} // parameterised
} // sesstype
