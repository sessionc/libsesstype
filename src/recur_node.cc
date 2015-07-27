#include <algorithm>
#include <string>

#include <sesstype/node.h>
#include <sesstype/node/recur.h>

namespace sesstype {

RecurNode::RecurNode(std::string label)
    : BlockNode(ST_NODE_RECUR),
      label_(label)
{
}

RecurNode::RecurNode(const RecurNode &node)
    : BlockNode(node),
      label_(node.label_)
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
}

std::string RecurNode::label() const
{
    return label_;
}

} // namespace sesstype
