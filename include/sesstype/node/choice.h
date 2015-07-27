#ifndef SESSTYPE__NODE__CHOICE_H__
#define SESSTYPE__NODE__CHOICE_H__

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
 * \brief Choice blocks.
 */
class ChoiceNode : public BlockNode {
  public:
    /// \brief ChoiceNode constructor with empty Role as default.
    ChoiceNode();

    /// \brief ChoiceNode constructor.
    /// \param[in] at Role (choice maker).
    ChoiceNode(Role *at);

    /// \brief ChoiceNode copy constructor.
    ChoiceNode(const ChoiceNode &node);

    /// \brief ChoiceNode destructor.
    ~ChoiceNode() override;

    /// \brief clone a ChoiceNode.
    ChoiceNode *clone() const override;

    /// \returns choice maker Role.
    Role *at() const;

    /// \param[in] at Role to set as choice maker.
    void set_at(Role *at);

    /// \param[in] choice Node to add as a branch.
    void add_choice(Node *choice);

    void accept(util::NodeVisitor &v) override;

  private:
    Role *at_;
};
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

st_node *st_mk_choice_node_init();
st_node *st_mk_choice_node(st_role *at);
Role *st_choice_node_get_at(st_node *node);
st_node *st_choice_node_set_at(st_node *node, st_role *at);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__NODE__CHOICE_H__
