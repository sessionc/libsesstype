#include <algorithm>
#include <iterator>
#include <string>
#include <unordered_map>
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
    delete from_;
    from_ = from->clone();
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
    to_.push_back(to->clone());
}

void InteractionNode::remove_tos()
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
    if (at_) delete at_;
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

// ParNode -------------------------------------------------------------------

ParNode::ParNode() : BlockNode(ST_NODE_PARALLEL)
{
}

ParNode::ParNode(const ParNode &node) : BlockNode(node)
{
}

ParNode::~ParNode()
{
}

ParNode *ParNode::clone() const
{
    return new ParNode(*this);
}

void ParNode::add_parallel(Node *parallel)
{
    append_child(parallel);
}

// NestedNode ----------------------------------------------------------------

NestedNode::NestedNode(std::string protocolname)
    : Node(ST_NODE_NESTED),
      name_(protocolname),
      scope_name_(),
      args_(),
      role_args_()
{
}

NestedNode::NestedNode(std::string protocolname, std::string scopename)
    : Node(ST_NODE_NESTED),
      name_(protocolname),
      scope_name_(scopename),
      args_(),
      role_args_()
{
}

NestedNode::NestedNode(const NestedNode &node)
    : Node(node),
      name_(node.name_),
      scope_name_(node.scope_name_),
      args_(),
      role_args_()
{
    for (auto arg : node.args_) {
        add_arg(arg->clone());
    }
    for (auto role_arg : node.role_args_) {
        add_arg(role_arg->clone());
    }
}

NestedNode::~NestedNode()
{
    for (auto arg : args_) {
        delete arg;
    }
    for (auto role_arg : role_args_) {
        delete role_arg;
    }
}

NestedNode *NestedNode::clone() const
{
    return new NestedNode(*this);
}

std::string NestedNode::name() const
{
    return name_;
}

std::string NestedNode::scope_name() const
{
    return scope_name_;
}

unsigned int NestedNode::num_arg() const
{
    return args_.size();
}

std::vector<MsgSig *>::const_iterator NestedNode::arg_begin() const
{
    return args_.begin();
}

std::vector<MsgSig *>::const_iterator NestedNode::arg_end() const
{
    return args_.end();
}

void NestedNode::add_arg(MsgSig *msg)
{
    args_.push_back(msg);
}

unsigned int NestedNode::num_rolearg() const
{
    return role_args_.size();
}

std::vector<Role *>::const_iterator NestedNode::rolearg_begin() const
{
    return role_args_.begin();
}

std::vector<Role *>::const_iterator NestedNode::rolearg_end() const
{
    return role_args_.end();
}

void NestedNode::add_arg(Role *role)
{
    role_args_.push_back(role);
}

// InterruptibleNode ---------------------------------------------------------

InterruptibleNode::InterruptibleNode()
    : BlockNode(ST_NODE_INTERRUPTIBLE),
      interrupts_(),
      scope_name_()
{
}

InterruptibleNode::InterruptibleNode(std::string scopename)
    : BlockNode(ST_NODE_INTERRUPTIBLE),
      interrupts_(),
      scope_name_(scopename)
{
}

InterruptibleNode::InterruptibleNode(const InterruptibleNode &node)
    : BlockNode(node),
      interrupts_(),
      scope_name_(node.scope_name_)
{
    for (auto interrupt : node.interrupts_) {
        Role *role = interrupt.first->clone();
        for (auto msg : interrupt.second) {
            add_interrupt(role, msg->clone());
        }
    }
}

InterruptibleNode::~InterruptibleNode()
{
    for (auto interrupt : interrupts_) {
        for (auto msg : interrupt.second) {
            delete msg;
        }
        delete interrupt.first; // Role
    }
}

InterruptibleNode *InterruptibleNode::clone() const
{
    return new InterruptibleNode(*this);
}

std::string InterruptibleNode::scope_name() const
{
    return scope_name_;
}

unsigned int InterruptibleNode::num_interrupt() const
{
    return interrupts_.size();
}

std::unordered_map<Role *, std::vector<MsgSig *>>::const_iterator InterruptibleNode::interrupt_begin() const
{
    return interrupts_.begin();
}

std::unordered_map<Role *, std::vector<MsgSig *>>::const_iterator InterruptibleNode::interrupt_end() const
{
    return interrupts_.end();
}

void InterruptibleNode::add_interrupt(Role *role, MsgSig *msg)
{
    auto it = std::find_if(interrupts_.begin(), interrupts_.end(),
        [role](std::pair<Role *, std::vector<MsgSig *>> role_msgs)
            -> bool { return role_msgs.first->name() == role->name(); });
    if (it == interrupts_.end()) {
        interrupts_.insert({ role, std::vector<MsgSig *>() });
    } else {
        (*it).second.push_back(msg);
    }
}

} // namespace sesstype
