#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <sesstype/expr.h>
#include <sesstype/message.h>
#include <sesstype/node.h>
#include <sesstype/role.h>

namespace sesstype {

// Node ----------------------------------------------------------------------

Node::Node(enum __st_node_type type) : type_(type)
{
}

Node::~Node()
{
}

enum __st_node_type Node::type() const
{
  return type_;
}

// BlockNode -----------------------------------------------------------------

BlockNode::BlockNode() : Node(ST_NODE_ROOT), children_()
{
}

BlockNode::BlockNode(enum __st_node_type type) : Node(type), children_()
{
}

BlockNode::~BlockNode()
{
  for (auto node : children_) {
    delete node;
  }
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
    : Node(ST_NODE_SENDRECV), msgsig_(new MsgSig("")),
      from_(NULL), to_(), msgcond_(NULL)
{
}

InteractionNode::InteractionNode(MsgSig *msgsig)
    : Node(ST_NODE_SENDRECV), msgsig_(msgsig),
      from_(NULL), to_(), msgcond_(NULL)
{
}

InteractionNode::~InteractionNode()
{
  delete msgsig_;
  if (msgcond_ != NULL) {
    delete msgcond_;
  }
  if (from_ != NULL) {
    delete from_;
  }
  for (auto it=to_begin(); it!=to_end(); it++) {
    delete *it;
  }
}

MsgCond *InteractionNode::cond() const
{
  return msgcond_;
}

void InteractionNode::set_cond(MsgCond *cond)
{
  // Note: only possible for send/receive.
  msgcond_ = cond;
}

void InteractionNode::set_msgsig(MsgSig *msgsig)
{
  msgsig_ = msgsig;
}

MsgSig *InteractionNode::msgsig() const
{
  return msgsig_;
}

void InteractionNode::set_from(Role *from)
{
  from_ = from;
}

Role *InteractionNode::from() const
{
  return from_;
}

Role *InteractionNode::to() const
{
  return to_.at(0);
}

unsigned int InteractionNode::num_to() const
{
  return to_.size();
}

Role *InteractionNode::to(unsigned int idx) const
{
  return to_.at(idx);
}

void InteractionNode::add_to(Role *to)
{
  to_.push_back(to);
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

RecurNode::~RecurNode()
{
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

ContinueNode::~ContinueNode()
{
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

ChoiceNode::~ChoiceNode()
{
  delete at_;
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

// ForNode -------------------------------------------------------------------

ForNode::ForNode(RngExpr *bind_expr)
    : BlockNode(ST_NODE_FOR), bind_expr_(bind_expr)
{
}

ForNode::~ForNode()
{
  if (bind_expr_ != NULL) {
    delete bind_expr_;
  }
}

void ForNode::set_bind_expr(RngExpr *bind_expr)
{
  if (bind_expr_ != NULL) {
    delete bind_expr_;
  }
  bind_expr_ = bind_expr;
}

RngExpr *ForNode::bind_expr() const
{
  if (bind_expr_ == NULL) {
    std::cerr << "Warning: bind_expr is NULL." << std::endl;
  }
  return bind_expr_;
}

// AllReduceNode -------------------------------------------------------------

AllReduceNode::AllReduceNode()
    : Node(ST_NODE_ALLREDUCE), msgsig_(new MsgSig(""))
{
}

AllReduceNode::AllReduceNode(MsgSig *msgsig)
    : Node(ST_NODE_ALLREDUCE), msgsig_(msgsig)
{
}

AllReduceNode::~AllReduceNode()
{
}

MsgSig* AllReduceNode::msgsig() const
{
  return msgsig_;
}

void AllReduceNode::set_msgsig(MsgSig *msgsig)
{
  msgsig_ = msgsig;
}


// OneofNode -----------------------------------------------------------------

OneofNode::OneofNode(Role *selector_role, unsigned int dimen)
    : BlockNode(ST_NODE_ONEOF),
      selector_role_(selector_role), selector_role_dimen_(dimen)
{
}

OneofNode::~OneofNode()
{
}

Role *OneofNode::selector_role() const
{
  return selector_role_;
}

unsigned int OneofNode::selector_role_dimen() const
{
  return selector_role_dimen_;
}

void OneofNode::set_selector_role(Role *selector_role, unsigned int dimen)
{
  selector_role_ = selector_role;
  selector_role_dimen_ = dimen;
}

bool OneofNode::unordered() const
{
  return unordered_;
}

void OneofNode::set_unordered(bool unordered)
{
  unordered_ = unordered;
}

// IfNode --------------------------------------------------------------------

IfNode::IfNode(MsgCond *cond) : BlockNode(ST_NODE_IF), cond_(cond)
{
}

IfNode::~IfNode()
{
  delete cond_;
}

Node *IfNode::body(unsigned int idx) const
{
  return child(idx);
}

void IfNode::append_body(Node *body)
{
  append_child(body);
}

MsgCond *IfNode::cond() const
{
  return cond_;
}

void IfNode::set_cond(MsgCond *cond)
{
  delete cond_;
  cond_ = cond;
}

} // namespace sesstype
