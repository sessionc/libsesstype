#include <sesstype/parameterised/node.h>
#include <sesstype/parameterised/cond.h>
#include <sesstype/parameterised/node/if.h>

namespace sesstype {
namespace parameterised {

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
