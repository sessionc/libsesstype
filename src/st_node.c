/**
 * @file
 * This file contains the tree representation of (multiparty) session
 * according to the Scribble language specification and provides functions
 * to build and manipulate session type trees.
 *
 * @headerfile "sesstype/st_expr.h"
 * @headerfile "sesstype/st_node.h"
 * @headerfile "sesstype/st_node_print.h"
 * @headerfile "sesstype/st_role.h"
 * @headerfile "sesstype/st_role_group.h"
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sesstype/st_expr.h"
#include "sesstype/st_node.h"
#include "sesstype/st_node_print.h"
#include "sesstype/st_role.h"
#include "sesstype/st_role_group.h"


st_tree *st_tree_init(st_tree *tree)
{
  assert(tree != NULL);
  tree->info = (st_info *)malloc(sizeof(st_info));
  tree->info->nimport = 0;
  tree->info->imports = NULL;
  tree->info->nconst = 0;
  tree->info->consts = NULL;
  tree->root = NULL;
  tree->info->nrole = 0;
  tree->info->roles = NULL;
  tree->info->ngroup = 0;
  tree->info->groups = NULL;
  tree->info->module = "default";

  return tree;
}


st_node *st_node_init(st_node *node, int type)
{
  assert(node != NULL);
  node->type = type;
  switch (type) {
    case ST_NODE_ROOT:
      break;
    case ST_NODE_SENDRECV:
    case ST_NODE_SEND:
    case ST_NODE_RECV:
      node->interaction = (st_node_interaction_t *)malloc(sizeof(st_node_interaction_t));
      node->interaction->msg_cond = NULL;
      break;
    case ST_NODE_PARALLEL:
      break;
    case ST_NODE_CHOICE:
      node->choice = (st_node_choice_t *)malloc(sizeof(st_node_choice_t));
      memset(node->choice, 0, sizeof(st_node_choice_t));
      break;
    case ST_NODE_RECUR:
      node->recur = (st_node_recur_t *)malloc(sizeof(st_node_recur_t));
      memset(node->recur, 0, sizeof(st_node_recur_t));
      break;
    case ST_NODE_CONTINUE:
      node->cont = (st_node_continue_t *)malloc(sizeof(st_node_continue_t));
      memset(node->cont, 0, sizeof(st_node_continue_t));
      break;
    case ST_NODE_FOR:
      node->forloop = (st_node_for_t *)malloc(sizeof(st_node_for_t));
      memset(node->forloop, 0, sizeof(st_node_for_t));
      break;
    case ST_NODE_ALLREDUCE:
      node->allreduce = (st_node_allreduce_t *)malloc(sizeof(st_node_allreduce_t));
      memset(node->allreduce, 0, sizeof(st_node_allreduce_t));
      break;
    case ST_NODE_IFBLK:
      node->ifblk = (st_node_ifblk_t *)malloc(sizeof(st_node_ifblk_t));
      memset(node->ifblk, 0, sizeof(st_node_ifblk_t));
      break;
#ifdef PABBLE_DYNAMIC
    case ST_NODE_ONEOF:
      node->oneof = (st_node_oneof_t *)malloc(sizeof(st_node_oneof_t));
      memset(node->oneof, 0, sizeof(st_node_oneof_t));
      break;
#endif
    default:
      fprintf(stderr, "%s:%d %s Unknown node type: %d\n", __FILE__, __LINE__, __FUNCTION__, type);
      break;
  }
  node->nchild = 0;
  node->children = NULL;
  node->marked = 0;

  return node;
}


st_node_msgsig_t st_node_msgsig_add_payload(st_node_msgsig_t msgsig, st_node_msgsig_payload_t payload)
{
  msgsig.payloads = (st_node_msgsig_payload_t *)realloc(msgsig.payloads, sizeof(st_node_msgsig_payload_t) * (msgsig.npayload+1));
  msgsig.payloads[msgsig.npayload].name = strdup(payload.name);
  msgsig.payloads[msgsig.npayload].type = strdup(payload.type);
  msgsig.payloads[msgsig.npayload].expr = st_expr_copy(payload.expr);
  msgsig.npayload++;
  return msgsig;
}


st_tree *st_tree_set_module(st_tree *tree, const char *module)
{
  assert(tree != NULL);
  tree->info->module = strdup(module);

  return tree;
}


st_tree *st_tree_set_name(st_tree *tree, const char *name)
{
  assert(tree != NULL);
  if (tree->info->name != NULL) free(tree->info->name);
  tree->info->name = strdup(name);
  tree->info->type = ST_TREE_GLOBAL;
  tree->info->myrole = NULL;

  return tree;
}


st_tree *st_tree_set_local_name(st_tree *tree, const char *name, const st_role *endpoint_role)
{
  assert(tree != NULL);
#ifdef __DEBUG__
  if (endpoint_role->dimen == 0) {
    fprintf(stderr, "%s: Endpoint: %s @ %s\n", __FUNCTION__, name, endpoint_role->name);
  } else {
    fprintf(stderr, "%s: Parameterised Endpoint: %s @ %s[%u-dimen]\n", __FUNCTION__, name, endpoint_role->name, endpoint_role->dimen);
  }
#endif
  tree->info->name = strdup(name);
  tree->info->type = ST_TREE_LOCAL;
  tree->info->myrole = st_role_init((st_role *)malloc(sizeof(st_role)));
  st_role_set_name(tree->info->myrole, endpoint_role->name);
  for (int p=0; p<endpoint_role->dimen; p++) {
    st_role_add_param(tree->info->myrole, st_expr_copy(endpoint_role->param[p]));
  }

  return tree;
}


st_tree *st_tree_add_const(st_tree *tree, st_const_t con)
{
  assert(tree != NULL && tree->info != NULL);
  tree->info->consts = (st_const_t **)realloc(tree->info->consts, sizeof(st_const_t *) * (tree->info->nconst+1));
  tree->info->consts[tree->info->nconst] = (st_const_t *)malloc(sizeof(st_const_t));
  memcpy(tree->info->consts[tree->info->nconst], &con, sizeof(st_const_t));
  tree->info->consts[tree->info->nconst]->name = strdup(con.name);
  tree->info->nconst++;

  return tree;
}


st_tree *st_tree_add_role(st_tree *tree, const st_role *role)
{
  assert(tree != NULL && tree->info != NULL);
  tree->info->roles = (st_role **)realloc(tree->info->roles, sizeof(st_role *) * (tree->info->nrole+1));
  tree->info->roles[tree->info->nrole] = st_role_copy(role);
  tree->info->nrole++;

  return tree;
}


st_tree *st_tree_add_role_group(st_tree *tree, const st_role_group *grp)
{
  assert(tree != NULL && tree->info != NULL);
  tree->info->groups = (st_role_group **)realloc(tree->info->groups, sizeof(st_role *) * (tree->info->ngroup+1));
  tree->info->groups[tree->info->ngroup] = st_role_group_copy(grp);
  tree->info->ngroup++;

  return tree;
}


st_tree *st_tree_add_import(st_tree *tree, st_tree_import_t import)
{
  assert(tree != NULL && tree->info != NULL);
  tree->info->imports = (st_tree_import_t **)realloc(tree->info->imports, sizeof(st_tree_import_t *) * (tree->info->nimport+1));
  tree->info->imports[tree->info->nimport] = (st_tree_import_t *)malloc(sizeof(st_tree_import_t));
  memcpy(tree->info->imports[tree->info->nimport], &import, sizeof(st_tree_import_t));
  tree->info->nimport++;

  return tree;
}


int st_tree_has_constant(st_tree *tree, const char *name)
{
  for (int constant=0; constant<tree->info->nconst; constant++) {
    if (strcmp(name, tree->info->consts[constant]->name) == 0) {
      return 1;
    }
  }
  return 0;
}


st_node *st_node_append(st_node *node, st_node *child)
{
  assert(node != NULL);
  assert(child != NULL);
  node->children = (st_node **)realloc(node->children, sizeof(st_node *) * (node->nchild+1));
  node->children[node->nchild] = child;
  node->nchild++;

  return node;
}


void st_node_reset_markedflag(st_node *node)
{
  int i = 0;
  assert(node != NULL);
  node->marked = 0;

  for (i=0; i<node->nchild; ++i) {
    st_node_reset_markedflag(node->children[i]);
  }
}


void st_node_free(st_node *node)
{
  for (int i=0; i<node->nchild; ++i) {
    st_node_free(node->children[i]);
  }
  if (node->nchild > 0) {
    free(node->children);
  }
  node->nchild = 0;

  switch (node->type) {
    case ST_NODE_ROOT:
      break;
    case ST_NODE_SENDRECV:
    case ST_NODE_SEND:
    case ST_NODE_RECV:
      free(node->interaction);
      break;
    case ST_NODE_PARALLEL:
      break;
    case ST_NODE_CHOICE:
      free(node->choice);
      break;
    case ST_NODE_RECUR:
      free(node->recur);
      break;
    case ST_NODE_CONTINUE:
      free(node->cont);
      break;
    case ST_NODE_FOR:
      free(node->forloop);
      break;
    case ST_NODE_ALLREDUCE:
      free(node->allreduce);
      break;
    case ST_NODE_IFBLK:
      free(node->ifblk);
      break;
#ifdef PABBLE_DYNAMIC
    case ST_NODE_ONEOF:
      free(node->oneof);
      break;
#endif
    default:
      fprintf(stderr, "%s:%d %s Unknown node type: %d\n", __FILE__, __LINE__, __FUNCTION__, node->type);
      break;
  }

  free(node);
}


void st_tree_free(st_tree *tree)
{
  assert(tree != NULL);
  if (tree->info != NULL) {
    free(tree->info);
  }
  if (tree->root == NULL) {
    st_node_free(tree->root);
  }
}
