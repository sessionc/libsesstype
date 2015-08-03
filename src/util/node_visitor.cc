#include <sesstype/msg.h>
#include <sesstype/role.h>
#include <sesstype/node.h>
#include <sesstype/node/block.h>
#include <sesstype/node/interaction.h>
#include <sesstype/node/choice.h>
#include <sesstype/node/recur.h>
#include <sesstype/node/continue.h>
#include <sesstype/node/par.h>
#include <sesstype/node/nested.h>
#include <sesstype/node/interruptible.h>

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

} // namespace sesstype
