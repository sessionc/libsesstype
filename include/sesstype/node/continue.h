#ifndef SESSTYPE__NODE__CONTINUE_H__
#define SESSTYPE__NODE__CONTINUE_H__

#ifdef __cplusplus
#include <string>
#endif

#include "sesstype/msg.h"
#include "sesstype/role.h"
#include "sesstype/node.h"
#include "sesstype/node/block.h"

#ifdef __cplusplus
namespace sesstype {
#endif

#ifdef __cplusplus
/**
 * \brief Continue statements.
 */
template <class BaseNode, class RoleType, class MessageType, class VisitorType>
class ContinueNodeTmpl : public BaseNode {
    std::string label_;

  public:
    /// \brief ContinueNode constructor.
    /// \param[in] label of Choice Node.
    ContinueNodeTmpl(std::string label)
        : BaseNode(ST_NODE_CONTINUE),
          label_(label) { }

    /// \brief ContinueNode copy constructor.
    ContinueNodeTmpl(const ContinueNodeTmpl &node)
        : BaseNode(ST_NODE_CONTINUE),
          label_(node.label_) { }

    /// \brief clone a ContinueNode.
    ContinueNodeTmpl *clone() const override
    {
        return new ContinueNodeTmpl(*this);
    }

    /// \brief Repalce label of ContinueNode.
    /// \param[in] label of ContinueNode to replace with.
    void set_label(std::string label)
    {
        label_ = label;
    }

    /// \returns label of ContinueNode.
    std::string label() const
    {
        return label_;
    }

    void accept(VisitorType &v) override;
};

using ContinueNode = ContinueNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

st_node *st_mk_continue_node(char *label);

st_node *st_continue_node_set_label(st_node *node, char *label);

const char *st_continue_node_get_label(st_node *node);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namspace sesstype
#endif

#endif//SESSTYPE__NODE__CONTINUE_H__
