#include <sesstype/node.h>
#include <sesstype/utils.h>

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

void ForNode::accept(utils::NodeVisitor &v)
{
  v.visit(this);
}

void OneofNode::accept(utils::NodeVisitor &v)
{
  v.visit(this);
}

void ChoiceNode::accept(utils::NodeVisitor &v)
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

} // namespace sesstype
