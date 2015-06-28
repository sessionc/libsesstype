#include <iostream>
#include <string>

#include <sesstype/node.h>
#include <sesstype/msg.h>
#include <sesstype/parameterised/expr.h>
#include <sesstype/parameterised/msg.h>
#include <sesstype/parameterised/node.h>

namespace sesstype {
namespace parameterised {


// InteractionNode -----------------------------------------------------------

InteractionNode::InteractionNode() : sesstype::InteractionNode(), msgcond_(nullptr)
{
}

InteractionNode::InteractionNode(MsgSig *msgsig)
    : sesstype::InteractionNode(msgsig), msgcond_(nullptr)
{
}

InteractionNode::InteractionNode(const sesstype::InteractionNode &node)
    : sesstype::InteractionNode(node), msgcond_(nullptr)
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

// ForNode -------------------------------------------------------------------

ForNode::ForNode(RngExpr *bind_expr)
    : BlockNode(ST_NODE_FOR), bind_expr_(bind_expr)
{
}

ForNode::ForNode(const ForNode &node)
    : BlockNode(node), bind_expr_(node.bind_expr_)
{
}

ForNode::~ForNode()
{
    if (bind_expr_ != NULL) {
        delete bind_expr_;
    }
}

ForNode *ForNode::clone() const
{
    return new ForNode(*this);
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
        std::cerr << "Warning: bind_expr is NULL.\n";
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

AllReduceNode::AllReduceNode(const AllReduceNode &node)
    : Node(ST_NODE_ALLREDUCE), msgsig_(node.msgsig_)
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
    msgsig_ = msgsig;
}


// OneofNode -----------------------------------------------------------------

OneofNode::OneofNode(Role *selector_role, unsigned int dimen)
    : BlockNode(ST_NODE_ONEOF),
      selector_role_(selector_role),
      selector_role_dimen_(dimen),
      unordered_(false)

{
}

OneofNode::OneofNode(const OneofNode &node)
    : BlockNode(node),
      selector_role_(node.selector_role_),
      selector_role_dimen_(node.selector_role_dimen_),
      unordered_(false)
{
}

OneofNode::~OneofNode()
{
}

OneofNode *OneofNode::clone() const
{
    return new OneofNode(*this);
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

IfNode::IfNode(const IfNode &node) : BlockNode(node), cond_(node.cond_)
{
}

IfNode::~IfNode()
{
    delete cond_;
}

IfNode *IfNode::clone() const
{
    return new IfNode(*this);
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

} // namespace parameterised
} // namespace sesstype
