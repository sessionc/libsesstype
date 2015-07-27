#include <string>

#include <sesstype/node.h>
#include <sesstype/node/continue.h>

namespace sesstype {

ContinueNode::ContinueNode(std::string label)
    : Node(ST_NODE_CONTINUE),
      label_(label)
{
}

ContinueNode::ContinueNode(const ContinueNode &node)
    : Node(ST_NODE_CONTINUE),
      label_(node.label_)
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
}

std::string ContinueNode::label() const
{
    return label_;
}

} // namespace sesstype
