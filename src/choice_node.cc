#include <sesstype/node.h>
#include <sesstype/role.h>
#include <sesstype/node/choice.h>

namespace sesstype {

ChoiceNode::ChoiceNode() : BlockNode(ST_NODE_CHOICE), at_()
{
}

ChoiceNode::ChoiceNode(Role *at) : BlockNode(ST_NODE_CHOICE), at_(at)
{
}

ChoiceNode::ChoiceNode(const ChoiceNode &node) : BlockNode(node), at_(node.at_)
{
}

ChoiceNode::~ChoiceNode()
{
    delete at_;
}

ChoiceNode *ChoiceNode::clone() const
{
    return new ChoiceNode(*this);
}

void ChoiceNode::set_at(Role *at)
{
    delete at_;
    at_ = at->clone();
}

Role *ChoiceNode::at() const
{
    return at_;
}

void ChoiceNode::add_choice(Node *choice_blk)
{
    append_child(choice_blk);
}

} // namespace sesstype
