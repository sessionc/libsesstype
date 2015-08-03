#ifndef SESSTYPE__NODE__RECUR_H__
#define SESSTYPE__NODE__RECUR_H__

#ifdef __cplusplus
#include <string>
#endif

#include "sesstype/msg.h"
#include "sesstype/role.h"
#include "sesstype/node.h"
#include "sesstype/node/block.h"
#include "sesstype/util/clonable.h"
#include "sesstype/util/visitor_tmpl.h"

#ifdef __cplusplus
namespace sesstype {
#endif

#ifdef __cplusplus
/**
 * \brief Recursion statements.
 */
template <class BaseNode, class RoleType, class MessageType, class VisitorType>
class RecurNodeTmpl : public BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType> {
    std::string label_;

  public:
    /// \brief RecurNode constructor.
    /// \param[in] label of RecurNode.
    RecurNodeTmpl(std::string label)
        : BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>(ST_NODE_RECUR),
          label_(label) { }

    /// \brief RecurNode copy constructor.
    RecurNodeTmpl(const RecurNodeTmpl &node)
        : BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>(node),
          label_(node.label_) { }

    /// \brief clone a RecurNode.
    RecurNodeTmpl *clone() const override
    {
        return new RecurNodeTmpl(*this);
    }

    /// \brief Replace label of RecurNode.
    /// \param[in] label of RecurNode to replace with.
    void set_label(std::string label)
    {
        label_ = label;
    }

    /// \returns label of RecursionNode.
    std::string label() const
    {
        return label_;
    }

    void accept(VisitorType &v) override;
};

using RecurNode = RecurNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

st_node *st_mk_recur_node(char *label);

st_node *st_recur_node_set_label(st_node *node, char *label);

const char *st_recur_node_get_label(st_node *node);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__NODE__RECUR_H__
