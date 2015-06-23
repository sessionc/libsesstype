#include <sesstype/node.h>
#include <sesstype/role.h>

#ifdef __cplusplus
namespace sesstype {
#endif

st_node *st_node_mk_interaction()
{
  return new InteractionNode();
}

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

st_node *st_node_mk_for(st_expr *bind_expr)
{
  return new ForNode(static_cast<RngExpr *>(bind_expr));
}

st_node *st_node_mk_allreduce()
{
  return new AllReduceNode();
}

st_node *st_node_mk_oneof(st_role *role, unsigned int dimen)
{
  return new OneofNode(role, dimen);
}

void st_node_free(st_node *node)
{
  if (InteractionNode *_node = static_cast<InteractionNode *>(node)) {
    delete _node;
  } else if (ChoiceNode *_node = static_cast<ChoiceNode *>(node)) {
    delete _node;
  } else if (RecurNode *_node = static_cast<RecurNode *>(node)) {
    delete _node;
  } else if (ContinueNode *_node = static_cast<ContinueNode *>(node)) {
    delete _node;
  } else if (ForNode *_node = static_cast<ForNode *>(node)) {
    delete _node;
  } else if (AllReduceNode *_node = static_cast<AllReduceNode *>(node)) {
    delete _node;
  } else if (OneofNode *_node = static_cast<OneofNode *>(node)) {
    delete _node;
  } else if (IfNode *_node = static_cast<IfNode *>(node)) {
    delete _node;
  }
}

#ifdef __cplusplus
} // namespace sesstype
#endif
