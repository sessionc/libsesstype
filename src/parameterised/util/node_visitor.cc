#include <sesstype/node/interaction.h>
#include <sesstype/node/choice.h>
#include <sesstype/node/recur.h>
#include <sesstype/node/continue.h>
#include <sesstype/node/par.h>
#include <sesstype/node/nested.h>
#include <sesstype/node/interruptible.h>
#include <sesstype/parameterised/node/for.h>
#include <sesstype/parameterised/node/allreduce.h>
#include <sesstype/parameterised/node/oneof.h>
#include <sesstype/parameterised/node/if.h>

#include <sesstype/parameterised/msg.h>
#include <sesstype/parameterised/role.h>
#include <sesstype/parameterised/node.h>

#include <sesstype/parameterised/util/node_visitor.h>
#include <sesstype/util/node_visitor.h>
#include <sesstype/util/visitor_tmpl.h>

namespace sesstype {

template <class BaseNode, class RoleType, class MessageType, class VisitorType>
void BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>::accept(VisitorType &v)
{
    v.visit(this);
}

template <class BaseNode, class RoleType, class MessageType, class VisitorType>
void InteractionNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>::accept(VisitorType &v)
{
    v.visit(this);
}

template <class BaseNode, class RoleType, class MessageType, class VisitorType>
void ChoiceNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>::accept(VisitorType &v)
{
    v.visit(this);
}

template <class BaseNode, class RoleType, class MessageType, class VisitorType>
void RecurNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>::accept(VisitorType &v)
{
    v.visit(this);
}

template <class BaseNode, class RoleType, class MessageType, class VisitorType>
void ContinueNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>::accept(VisitorType &v)
{
    v.visit(this);
}

template <class BaseNode, class RoleType, class MessageType, class VisitorType>
void ParNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>::accept(VisitorType &v)
{
    v.visit(this);
}

template <class BaseNode, class RoleType, class MessageType, class VisitorType>
void NestedNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>::accept(VisitorType &v)
{
    v.visit(this);
}

template <class BaseNode, class RoleType, class MessageType, class VisitorType>
void InterruptibleNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>::accept(VisitorType &v)
{
    v.visit(this);
}

namespace parameterised {

void InteractionNode::accept(util::NodeVisitor &v)
{
    v.visit(this);
}

template <class BaseNode, class RoleType, class MessageType, class VisitorType>
void ForNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>::accept(VisitorType &v)
{
    v.visit(this);
}

template <class BaseNode, class RoleType, class MessageType, class VisitorType>
void AllReduceNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>::accept(VisitorType &v)
{
    v.visit(this);
}

template <class BaseNode, class RoleType, class MessageType, class VisitorType>
void OneofNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>::accept(VisitorType &v)
{
    v.visit(this);
}

template <class BaseNode, class RoleType, class MessageType, class VisitorType>
void IfNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>::accept(VisitorType &v)
{
    v.visit(this);
}

} // namespace parameterised
} // namespace sesstype
