#include <sesstype/node.h>
#include <sesstype/node/par.h>

namespace sesstype {

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

void ParNode::add_parallel(Node *par_blk)
{
    append_child(par_blk);
}

} // namespace sesstype
