#ifndef SESSTYPE__NODE__NESTED_H__
#define SESSTYPE__NODE__NESTED_H__

#ifdef __cplusplus
#include <string>
#include <iterator>
#include <vector>
#endif

#include "sesstype/msg.h"
#include "sesstype/node.h"
#include "sesstype/role.h"
#include "sesstype/util/clonable.h"
#include "sesstype/util/visitor_tmpl.h"

#ifdef __cplusplus
namespace sesstype {
#endif

#ifdef __cplusplus
/**
 * \brief Nested session type.
 */
template <class BaseNode, class RoleType, class MessageType, class VisitorType>
class NestedNodeTmpl : public BaseNode {
    std::string name_;
    std::string scope_;
    typename std::vector<MessageType *> args_;
    typename std::vector<RoleType *> role_args_;

  public:
    /// \brief NestedNode constructor with no scope name by default.
    NestedNodeTmpl(std::string protocol_name)
        : BaseNode(ST_NODE_NESTED),
        name_(protocol_name), scope_(), args_(), role_args_() { }

    /// \brief NestedNode constructor.
    NestedNodeTmpl(std::string protocol_name, std::string scope)
        : BaseNode(ST_NODE_NESTED),
          name_(protocol_name), scope_(scope), args_(), role_args_() { }

    /// \brief NestedNode copy constructor.
    NestedNodeTmpl(const NestedNodeTmpl &node)
        : BaseNode(node),
          name_(node.name_), scope_(node.scope_), args_(), role_args_()
    {
        for (auto arg : node.args_) {
            add_arg(arg->clone());
        }
        for (auto role_arg : node.role_args_) {
            add_arg(role_arg->clone());
        }
    }

    /// \brief NestedNode destructor.
    ~NestedNodeTmpl() override
    {
        for (auto arg : args_) {
            delete arg;
        }
        for (auto role_arg : role_args_) {
            delete role_arg;
        }
    }

    /// \brief clone a NestedNode.
    NestedNodeTmpl *clone() const override
    {
        return new NestedNodeTmpl(*this);
    }

    /// \returns name of nested session to execute.
    std::string name() const
    {
        return name_;
    }

    /// \param[in] scope_name to use for this NestedNode
    void set_scope(std::string scope)
    {
        scope_ = scope;
    }

    /// \returns scope name.
    std::string scope() const
    {
        return scope_;
    }

    /// \brief add message instantiation arguments.
    /// \param[in] arg for instantiation of message parameter.
    void add_arg(MessageType *msg)
    {
        args_.push_back(msg);
    }

    /// \returns number of Message arguments.
    unsigned int num_args() const
    {
        return args_.size();
    }

    MessageType *arg(unsigned int idx) const
    {
        return args_.at(idx);
    }

    typename std::vector<MessageType *>::const_iterator arg_begin() const
    {
        return args_.begin();
    }

    typename std::vector<MessageType *>::const_iterator arg_end() const
    {
        return args_.end();
    }

    /// \brief add role instantiation arguments.
    /// \param[in] role for instantiation of protocol.
    void add_arg(RoleType *role)
    {
        role_args_.push_back(role);
    }

    /// \returns number of Role arguments.
    unsigned int num_roleargs() const
    {
        return role_args_.size();
    }


    RoleType *rolearg(unsigned int idx) const
    {
        return role_args_.at(idx);
    }

    typename std::vector<RoleType *>::const_iterator rolearg_begin() const
    {
        return role_args_.begin();
    }

    typename std::vector<RoleType *>::const_iterator rolearg_end() const
    {
        return role_args_.end();
    }

    void accept(VisitorType &v) override;
};

using NestedNode = NestedNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

st_node *st_mk_nested_node(char *protocol_name);
st_node *st_mk_nested_node_scoped(char *protocol_name, char *scope_name);

st_node *st_nested_node_add_arg(st_node *node, st_msg *arg);
unsigned int st_nested_node_num_args(st_node *node);
st_msg *st_nested_node_get_arg(st_node *node, unsigned int index);

st_node *st_nested_node_add_rolearg(st_node *node, st_role *rolearg);
unsigned int st_nested_node_num_roleargs(st_node *node);
st_role *st_nested_node_get_rolearg(st_node *node, unsigned int index);

#ifdef __cplusplus
} // extern "C"
#endif


#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__NODE__NESTED_H__
