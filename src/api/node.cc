#include <sesstype/node.h>
#include <sesstype/role.h>

#ifdef __cplusplus
namespace sesstype {
#endif

st_node *st_node_mk_recur(char *label)
{
  return new RecurNode(label);
}

st_node *st_node_mk_continue(char *label)
{
  return new ContinueNode(label);
}

st_node *st_node_mk_choice(st_role *at_role)
{
  return new ChoiceNode(at_role);
}

#ifdef __cplusplus
} // namespace sesstype
#endif
