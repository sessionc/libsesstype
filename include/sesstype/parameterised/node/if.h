#ifndef SESSTYPE__PARAMETERISED__NODE__IF_H__
#define SESSTYPE__PARAMETERISED__NODE__IF_H__

#include "sesstype/node/block.h"
#include "sesstype/util/visitor_tmpl.h"

#include "sesstype/parameterised/msg.h"
#include "sesstype/parameterised/cond.h"
#include "sesstype/parameterised/role.h"
#include "sesstype/parameterised/node.h"


#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief If-block.
 */
template <class BaseNode, class RoleType, class MessageType, class VisitorType>
class IfNodeTmpl : public BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType> {
    MsgCond *cond_;

  public:
    /// \brief IfNode constructor.
    /// \param[in] cond for the if-block.
    IfNodeTmpl(MsgCond *cond)
        : BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>(ST_NODE_IF),
          cond_(cond) { }

    /// \brief IfNode copy constructor.
    IfNodeTmpl(const IfNodeTmpl &node)
        : BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>(node),
          cond_(node.cond_) { }

    /// \brief IfNode destructor.
    ~IfNodeTmpl() override
    {
        delete cond_;
    }

    /// \brief clone a IfNode.
    IfNodeTmpl *clone() const override
    {
        return new IfNodeTmpl(*this);
    }

    /// \brief Get body Node at position <tt>idx</tt>.
    /// \param[in] idx of Node in IfNode.
    /// \returns body Node at position <tt>idx</tt>
    BaseNode *body() const
    {
        return BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>::child(0);
    }

    /// \brief Add body Node to current if-block
    /// \param[in] body Node.
    void set_body(BaseNode *body)
    {
        this->set_child(0, body);
    }

    /// \returns if-block condition.
    MsgCond *cond() const
    {
        return cond_;
    }

    /// \brief Set if-block condition.
    /// \param[in] cond for the if-block.
    void set_cond(MsgCond *cond)
    {
        cond_ = cond;
    }

    void virtual accept(VisitorType &v) override;
};

using IfNode = IfNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

st_node *st_mk_if_node(st_cond *cond);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__NODE__IF_H__
