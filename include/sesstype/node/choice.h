#ifndef SESSTYPE__NODE__CHOICE_H__
#define SESSTYPE__NODE__CHOICE_H__

#include "sesstype/msg.h"
#include "sesstype/node.h"
#include "sesstype/role.h"
#include "sesstype/node/block.h"

#ifdef __cplusplus
namespace sesstype {
#endif

#ifdef __cplusplus
/**
 * \brief Choice blocks.
 */
template <class BaseNode, class RoleType, class MessageType, class VisitorType>
class ChoiceNodeTmpl : public BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType> {
    RoleType *at_;

  public:
    /// \brief ChoiceNode constructor with empty Role as default.
    ChoiceNodeTmpl()
        : BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>(ST_NODE_CHOICE),
          at_() { }

    /// \brief ChoiceNode constructor.
    /// \param[in] at Role (choice maker).
    ChoiceNodeTmpl(RoleType *at)
        : BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>(ST_NODE_CHOICE),
          at_(at) { }

    /// \brief ChoiceNode copy constructor.
    ChoiceNodeTmpl(const ChoiceNodeTmpl &node)
        : BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>(node),
          at_(node.at_) { }

    /// \brief ChoiceNode destructor.
    ~ChoiceNodeTmpl() override
    {
        delete at_;
    }

    /// \brief clone a ChoiceNode.
    ChoiceNodeTmpl *clone() const override
    {
        return new ChoiceNodeTmpl(*this);
    }

    /// \param[in] at Role to set as choice maker.
    void set_at(RoleType *at)
    {
        delete at_;
        at_ = at->clone();
    }

    /// \returns choice maker Role.
    RoleType *at() const
    {
        return at_;
    }

    /// \param[in] choice Node to add as a branch.
    void add_choice(BaseNode *choice)
    {
        this->append_child(choice);
    }

    void accept(VisitorType &v) override;
};

using ChoiceNode = ChoiceNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

st_node *st_mk_choice_node_init();

st_node *st_mk_choice_node(st_role *at);

st_role *st_choice_node_get_at(st_node *node);

st_node *st_choice_node_set_at(st_node *node, st_role *at);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__NODE__CHOICE_H__
