#include <sesstype/parameterised/node.h>
#include <sesstype/parameterised/node/interaction.h>
#include <sesstype/parameterised/node/choice.h>
#include <sesstype/parameterised/node/recur.h>
#include <sesstype/parameterised/node/continue.h>
#include <sesstype/parameterised/node/par.h>
#include <sesstype/parameterised/node/nested.h>
#include <sesstype/parameterised/node/interruptible.h>
#include <sesstype/parameterised/node/for.h>
#include <sesstype/parameterised/node/allreduce.h>
#include <sesstype/parameterised/node/oneof.h>
#include <sesstype/parameterised/node/if.h>

#include <sesstype/parameterised/util/node_visitor.h>

namespace sesstype {
namespace parameterised {

void InteractionNode::accept(sesstype::util::NodeVisitor &v)
{
    v.visit(this);
}

void ForNode::accept(sesstype::util::NodeVisitor &v)
{
    v.visit(this);
}

void AllReduceNode::accept(sesstype::util::NodeVisitor &v)
{
    v.visit(this);
}

void OneofNode::accept(sesstype::util::NodeVisitor &v)
{
    v.visit(this);
}

void IfNode::accept(sesstype::util::NodeVisitor &v)
{
    v.visit(this);
}

} // namespace parameterised
} // namespace sesstype
