#include <vector>

#include <sesstype/node.h>

namespace sesstype {

BlockNode::BlockNode() : Node(ST_NODE_ROOT), children_()
{
}

BlockNode::BlockNode(int type) : Node(type), children_()
{
}

BlockNode::BlockNode(const BlockNode &node) : Node(ST_NODE_ROOT), children_()
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

unsigned int BlockNode::num_children() const
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

} // namespace sesstype
