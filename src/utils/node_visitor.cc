#include <sesstype/node.h>
#include <sesstype/parameterised/node.h>
#include <sesstype/utils/node.h>

namespace sesstype {

void InteractionNode::accept(utils::NodeVisitor &v)
{
    v.visit(this);
}

void BlockNode::accept(utils::NodeVisitor &v)
{
    v.visit(this);
}

void RecurNode::accept(utils::NodeVisitor &v)
{
    v.visit(this);
}

void ContinueNode::accept(utils::NodeVisitor &v)
{
    v.visit(this);
}

void ChoiceNode::accept(utils::NodeVisitor &v)
{
    v.visit(this);
}

void ParNode::accept(utils::NodeVisitor &v)
{
    v.visit(this);
}

void NestedNode::accept(utils::NodeVisitor &v)
{
    v.visit(this);
}

void InterruptibleNode::accept(utils::NodeVisitor &v)
{
    v.visit(this);
}

namespace parameterised {

void InteractionNode::accept(utils::NodeVisitor &v)
{
    v.visit(this);
}

void ForNode::accept(utils::NodeVisitor &v)
{
    v.visit(this);
}

void OneofNode::accept(utils::NodeVisitor &v)
{
    v.visit(this);
}


void AllReduceNode::accept(utils::NodeVisitor &v)
{
    v.visit(this);
}

void IfNode::accept(utils::NodeVisitor &v)
{
    v.visit(this);
}

} // namespace parameterised

} // namespace sesstype
