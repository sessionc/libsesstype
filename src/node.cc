#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <sesstype/msg.h>
#include <sesstype/node.h>
#include <sesstype/role.h>

namespace sesstype {

// Node ----------------------------------------------------------------------

Node::Node(int type) : type_(type)
{
}

Node::~Node()
{
}

int Node::type() const
{
    return type_;
}

// BlockNode -----------------------------------------------------------------

BlockNode::BlockNode() : Node(ST_NODE_ROOT), children_()
{
}

BlockNode::BlockNode(int type) : Node(type), children_()
{
}

BlockNode::BlockNode(const BlockNode &node)
    : Node(ST_NODE_ROOT), children_()
{
    for (auto node : node.children_) {
        children_.push_back(node->clone());
    }
}

BlockNode::~BlockNode()
{
    for (auto node : children_) {
        delete node;
    }
}

BlockNode *BlockNode::clone() const
{
    return new BlockNode(*this);
}

Node *BlockNode::child(unsigned int idx) const
{
    return children_.at(idx);
}

unsigned int BlockNode::num_child() const
{
    return children_.size();
}

void BlockNode::append_child(Node *child)
{
    children_.push_back(child);
}

std::vector<Node *>::const_iterator BlockNode::child_begin() const
{
    return children_.begin();
}

std::vector<Node *>::const_iterator BlockNode::child_end() const
{
    return children_.end();
}

// InteractionNode -----------------------------------------------------------

InteractionNode::InteractionNode()
    : Node(ST_NODE_SENDRECV), msgsig_(new MsgSig("")), from_(nullptr), to_()
{
}

InteractionNode::InteractionNode(MsgSig *msgsig)
    : Node(ST_NODE_SENDRECV), msgsig_(msgsig), from_(nullptr), to_()
{
}

InteractionNode::InteractionNode(const InteractionNode &node)
    : Node(ST_NODE_SENDRECV), msgsig_(node.msgsig_),
      from_(node.from_), to_(node.to_)
{
}

InteractionNode::~InteractionNode()
{
    delete msgsig_;
    if (from_ != nullptr) {
        delete from_;
    }
    for (auto it=to_begin(); it!=to_end(); it++) {
        delete *it;
    }
}

InteractionNode *InteractionNode::clone() const
{
    return new InteractionNode(*this);
}

void InteractionNode::set_msgsig(MsgSig *msgsig)
{
    msgsig_ = msgsig;
}

MsgSig *InteractionNode::msgsig() const
{
    return msgsig_;
}

Role *InteractionNode::from() const
{
    return from_;
}

void InteractionNode::set_from(Role *from)
{
    from_ = from;
}

void InteractionNode::remove_from()
{
    delete from_;
    from_ = nullptr;
}

Role *InteractionNode::to(unsigned int idx) const
{
    return to_.at(idx);
}

Role *InteractionNode::to() const
{
    return to_.at(0);
}

unsigned int InteractionNode::num_to() const
{
    return to_.size();
}

void InteractionNode::add_to(Role *to)
{
    to_.push_back(to);
}

void InteractionNode::remove_tos()
{
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

// RecurNode -----------------------------------------------------------------

RecurNode::RecurNode(std::string label)
    : BlockNode(ST_NODE_RECUR), label_(label)
{
    std::replace(label_.begin(), label_.end(), ' ', '_');
}

RecurNode::RecurNode(const RecurNode &node)
    : BlockNode(node), label_(node.label_)
{
}

RecurNode::~RecurNode()
{
}

RecurNode *RecurNode::clone() const
{
    return new RecurNode(*this);
}

void RecurNode::set_label(std::string label)
{
    label_ = label;
    std::replace(label_.begin(), label_.end(), ' ', '_');
}

std::string RecurNode::label() const
{
    return label_;
}

// ContinueNode --------------------------------------------------------------

ContinueNode::ContinueNode(std::string label)
    : Node(ST_NODE_CONTINUE), label_(label)
{
    std::replace(label_.begin(), label_.end(), ' ', '_');
}

ContinueNode::ContinueNode(const ContinueNode &node)
    : Node(ST_NODE_CONTINUE), label_(node.label_)
{
}

ContinueNode::~ContinueNode()
{
}

ContinueNode *ContinueNode::clone() const
{
    return new ContinueNode(*this);
}

void ContinueNode::set_label(std::string label)
{
    label_ = label;
    std::replace(label_.begin(), label_.end(), ' ', '_');
}

std::string ContinueNode::label() const
{
    return label_;
}

// ChoiceNode ----------------------------------------------------------------

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

void ChoiceNode::set_atrole(Role *at)
{
    at_ = at;
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
