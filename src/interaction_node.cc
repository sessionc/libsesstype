#include <iterator>
#include <vector>

#include <sesstype/msg.h>
#include <sesstype/node.h>
#include <sesstype/role.h>
#include <sesstype/node/interaction.h>

namespace sesstype {

InteractionNode::InteractionNode()
    : Node(ST_NODE_SENDRECV),
      msgsig_(new MsgSig("")),
      from_(),
      to_()
{
}

InteractionNode::InteractionNode(MsgSig *msgsig)
    : Node(ST_NODE_SENDRECV),
      msgsig_(msgsig->clone()),
      from_(),
      to_()
{
}

InteractionNode::InteractionNode(const InteractionNode &node)
    : Node(ST_NODE_SENDRECV),
      msgsig_(node.msgsig_->clone()),
      from_(node.from_->clone()),
      to_()
{
    for (auto to : node.to_) {
        to_.push_back(to->clone());
    }
}

InteractionNode::~InteractionNode()
{
    delete msgsig_;
    delete from_;
    for (Role *to : to_) {
        delete to;
    }
    to_.clear();
}

InteractionNode *InteractionNode::clone() const
{
    return new InteractionNode(*this);
}

void InteractionNode::set_msgsig(MsgSig *msgsig)
{
    delete msgsig_;
    msgsig_ = msgsig->clone();
}

MsgSig *InteractionNode::msgsig() const
{
    return msgsig_;
}

void InteractionNode::set_from(Role *from)
{
    delete from_;
    from_ = from->clone();
}

Role *InteractionNode::from() const
{
    return from_;
}

void InteractionNode::remove_from()
{
    delete from_;
}

void InteractionNode::add_to(Role *to)
{
    to_.push_back(to->clone());
}

unsigned int InteractionNode::num_tos() const
{
    return to_.size();
}

Role *InteractionNode::to() const
{
    return to_.at(0);
}

Role *InteractionNode::to(unsigned int idx) const
{
    return to_.at(idx);
}

void InteractionNode::clear_to()
{
    for (Role *to : to_) {
        delete to;
    }
    to_.clear();
}

std::vector<Role *>::const_iterator InteractionNode::to_begin() const
{
    return to_.begin();
}

std::vector<Role *>::const_iterator InteractionNode::to_end() const
{
    return to_.end();
}

} // namespace sesstype
