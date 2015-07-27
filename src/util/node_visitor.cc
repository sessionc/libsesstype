#include <sesstype/node.h>
#include <sesstype/node/interaction.h>
#include <sesstype/node/choice.h>
#include <sesstype/node/recur.h>
#include <sesstype/node/continue.h>
#include <sesstype/node/par.h>
#include <sesstype/node/nested.h>
#include <sesstype/node/interruptible.h>

#include <sesstype/util/node_visitor.h>

namespace sesstype {

void Node::accept(util::NodeVisitor &v)
{
    v.visit(this);
}

void BlockNode::accept(util::NodeVisitor &v)
{
    v.visit(this);
}

void InteractionNode::accept(util::NodeVisitor &v)
{
    v.visit(this);
}

void ChoiceNode::accept(util::NodeVisitor &v)
{
    v.visit(this);
}

void RecurNode::accept(util::NodeVisitor &v)
{
    v.visit(this);
}

void ContinueNode::accept(util::NodeVisitor &v)
{
    v.visit(this);
}

void ParNode::accept(util::NodeVisitor &v)
{
    v.visit(this);
}

void NestedNode::accept(util::NodeVisitor &v)
{
    v.visit(this);
}

void InterruptibleNode::accept(util::NodeVisitor &v)
{
    v.visit(this);
}

} // namespace sesstype
