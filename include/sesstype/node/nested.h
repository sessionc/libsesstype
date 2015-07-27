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

#ifdef __cplusplus
namespace sesstype {
namespace util {

class NodeVisitor;

} // namespace util
} // namespace sesstype
#endif

#ifdef __cplusplus
namespace sesstype {
#endif

#ifdef __cplusplus
/**
 * \brief Nested session type.
 */
class NestedNode : public virtual Node {
  public:
    /// \brief NestedNode constructor with no scope name by default.
    NestedNode(std::string protocol_name);

    /// \brief NestedNode constructor.
    NestedNode(std::string protocol_name, std::string scope_name);

    /// \brief NestedNode copy constructor.
    NestedNode(const NestedNode &node);

    /// \brief NestedNode destructor.
    ~NestedNode() override;

    /// \brief clone a NestedNode.
    NestedNode *clone() const override;

    /// \returns name of nested session to execute.
    std::string name() const;

    /// \param[in] scope_name to use for this NestedNode
    void set_scope(std::string scope_name);

    /// \returns scope name.
    std::string scope() const;

    /// \brief add message instantiation arguments.
    /// \param[in] arg for instantiation of message parameter.
    void add_arg(MsgSig *msg);

    /// \returns number of Message arguments.
    unsigned int num_args() const;

    MsgSig *arg(unsigned int index) const;

    std::vector<MsgSig *>::const_iterator arg_begin() const;
    std::vector<MsgSig *>::const_iterator arg_end() const;

    /// \brief add role instantiation arguments.
    /// \param[in] role for instantiation of protocol.
    void add_arg(Role *role);

    /// \returns number of Role arguments.
    unsigned int num_roleargs() const;

    Role *rolearg(unsigned int index) const;

    std::vector<Role *>::const_iterator rolearg_begin() const;
    std::vector<Role *>::const_iterator rolearg_end() const;

    void accept(util::NodeVisitor &v) override;

  private:
    std::string name_;
    std::string scope_name_;
    std::vector<MsgSig *> args_;
    std::vector<Role *> role_args_;
};
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
