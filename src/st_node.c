/**
 * \file
 * This file contains the tree representation of (multiparty) session
 * according to the Scribble language specification and provides functions
 * to build and manipulate session type trees.
 * 
 * \headerfile "st_node.h"
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sesstype/st_node.h"
#include "sesstype/st_expr.h"


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


void st_node_free(st_node *node)
{
  int i;
  for (i=0; i<node->nchild; ++i) {
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
    case ST_NODE_ONEOF:
      free(node->oneof);
      break;
    default:
      fprintf(stderr, "%s:%d %s Unknown node type: %d\n", __FILE__, __LINE__, __FUNCTION__, node->type);
      break;
  }

  free(node);
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
  tree->info->name = strdup(name);
  tree->info->type = ST_TYPE_GLOBAL;
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
    fprintf(stderr, "%s: Parameterised Endpoint: %s @ %s[%u-dimen]", __FUNCTION__, name, endpoint_role->name, endpoint_role->dimen);
  }
#endif
  tree->info->name = strdup(name);
  tree->info->type = ST_TYPE_LOCAL;
  tree->info->myrole = (st_role *)malloc(sizeof(st_role));
  tree->info->myrole->name = strdup(endpoint_role->name);
  tree->info->myrole->dimen = endpoint_role->dimen;
  tree->info->myrole->param = (st_expr **)malloc(sizeof(st_expr *));
  for (int i=0; i<endpoint_role->dimen; ++i) {
    tree->info->myrole->param[i] = st_expr_copy(endpoint_role->param[i]);
  }

  return tree;
}


st_tree *st_tree_add_const(st_tree *tree, st_const_t con)
{
  assert(tree != NULL);
  assert(tree->info != NULL);
  if (tree->info->nconst == 0) {
    tree->info->consts = (st_const_t **)malloc(sizeof(st_const_t *));
  } else if (tree->info->nrole > 0) {
    tree->info->consts = (st_const_t **)realloc(tree->info->consts, sizeof(st_const_t *) * (tree->info->nconst+1));
  }

  tree->info->consts[tree->info->nconst] = (st_const_t *)malloc(sizeof(st_const_t));
  memcpy(tree->info->consts[tree->info->nconst], &con, sizeof(st_const_t));
  tree->info->consts[tree->info->nconst]->name = strdup(con.name);
  tree->info->nconst++;
  return tree;
}


st_tree *st_tree_add_role(st_tree *tree, const st_role *role)
{
  assert(tree != NULL);
  assert(tree->info != NULL);
  if (tree->info->nrole == 0) {
    // Allocate for 1 element.
    tree->info->roles = (st_role **)malloc(sizeof(st_role *));
  } else if (tree->info->nrole > 0) {
    // Allocate for n+1 element.
    tree->info->roles = (st_role **)realloc(tree->info->roles, sizeof(st_role *) * (tree->info->nrole+1));
  }

  tree->info->roles[tree->info->nrole] = st_node_copy_role(role);
  tree->info->nrole++;

  return tree;
}


st_tree *st_tree_add_role_group(st_tree *tree, const st_role_group *group)
{
  assert(tree != NULL);
  assert(tree->info != NULL);
  if (tree->info->ngroup == 0) {
    // Allocate for 1 element.
    tree->info->groups = (st_role_group **)malloc(sizeof(st_role_group *));
  } else if (tree->info->ngroup > 0) {
    // Allocate for n+1 element.
    tree->info->groups = (st_role_group **)realloc(tree->info->groups, sizeof(st_role *) * (tree->info->ngroup+1));
  }

  tree->info->groups[tree->info->ngroup] = (st_role_group *)malloc(sizeof(st_role_group));
  tree->info->groups[tree->info->ngroup]->name = strdup(group->name);
  tree->info->groups[tree->info->ngroup]->nmemb = group->nmemb;
  tree->info->groups[tree->info->ngroup]->membs = (st_role **)malloc(sizeof(st_role *));
  for (int r=0; r<group->nmemb; ++r) {
    tree->info->groups[tree->info->ngroup]->membs[r] = st_node_copy_role(group->membs[r]);
  }

  tree->info->ngroup++;

  return tree;
}


st_tree *st_tree_add_import(st_tree *tree, st_tree_import_t import)
{
  assert(tree != NULL);
  if (tree->info == NULL) {
    tree->info = malloc(sizeof(st_info));
    tree->info->nrole = 0;
  }

  if (tree->info->nimport == 0) {
    // Allocate for 1 element.
    tree->info->imports = (st_tree_import_t **)malloc(sizeof(st_tree_import_t *));
  } else if (tree->info->nimport > 0) {
    // Allocate for n+1 element.
    tree->info->imports = (st_tree_import_t **)realloc(tree->info->imports, sizeof(st_tree_import_t *) * (tree->info->nimport+1));
  }

  tree->info->imports[tree->info->nimport] = (st_tree_import_t *)malloc(sizeof(st_tree_import_t));
  memcpy(tree->info->imports[tree->info->nimport], &import, sizeof(st_tree_import_t));

  tree->info->nimport++;

  return tree;
}

int st_tree_is_constant(st_tree *tree, const char *name)
{
  for (int constant=0; constant<tree->info->nconst; constant++) {
    if (strcmp(name, tree->info->consts[constant]->name) == 0) {
      return 1;
    }
  }
  return 0;
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
    case ST_NODE_ONEOF:
      node->oneof = (st_node_oneof_t *)malloc(sizeof(st_node_oneof_t));
      memset(node->oneof, 0, sizeof(st_node_oneof_t));
      break;
    default:
      fprintf(stderr, "%s:%d %s Unknown node type: %d\n", __FILE__, __LINE__, __FUNCTION__, type);
      break;
  }
  node->nchild = 0;
  node->marked = 0;

  return node;
}


st_node *st_node_append(st_node *node, st_node *child)
{
  assert(node != NULL);
  assert(child != NULL);
  if (node->nchild == 0) {
    // Allocate for 1 node.
    node->children = (st_node **)malloc(sizeof(st_node *));
  } else if (node->nchild > 0) {
    // Allocate for n+1 nodes.
    node->children = (st_node **)realloc(node->children, sizeof(st_node *) * (node->nchild+1));
  }

  node->children[node->nchild++] = child;

  return node;
}


void st_tree_print(const st_tree *tree)
{
  if (tree == NULL) {
    fprintf(stderr, "%s:%d %s tree is NULL\n", __FILE__, __LINE__, __FUNCTION__);
  }

  printf("\n-------Summary------\n");

  if (tree->info != NULL) {
    printf("Protocol: %s#%s\n", tree->info->module, tree->info->name);
    switch (tree->info->type) {
      case ST_TYPE_GLOBAL:
        printf("Global protocol\n");
        break;
      case ST_TYPE_LOCAL:
        printf("Local protocol\n");
        break;
      default:
        assert(0/* Unrecognised Type*/);
    }

    if (ST_TYPE_GLOBAL != tree->info->type) {
      if (tree->info->myrole != NULL) {
        printf("Endpoint role: %s", tree->info->myrole->name);
        for (int i=0; i<tree->info->myrole->dimen; ++i) {
          printf("[");
          st_expr_print(tree->info->myrole->param[i]);
          printf("]");
        }
      } else {
        printf("Endpoint role: NOT SET");
      }
    }
    printf("\n");

    printf("Imports: [");
    for (int i=0; i<tree->info->nimport; ++i) {
      if (i==0) printf("\n");
      printf("  { name: %s, as: %s, from: %s }\n",
          tree->info->imports[i]->name,
          tree->info->imports[i]->as,
          tree->info->imports[i]->from);
    }
    printf("]\n");

    printf("Constants: [");
    for (int c=0; c<tree->info->nconst; ++c) {
      printf("\n%s ", tree->info->consts[c]->name);
      switch (tree->info->consts[c]->type) {
        case ST_CONST_VALUE:
          printf("= %u",
              tree->info->consts[c]->value);
          break;
        case ST_CONST_BOUND:
          printf("is between %u and %u",
              tree->info->consts[c]->bounds.lbound,
              tree->info->consts[c]->bounds.ubound);
          break;
        case ST_CONST_INF:
          printf("is unbounded from %u to +Inf",
              tree->info->consts[c]->inf.lbound);
          break;
      }
    }
    printf("]\n");

    printf("Roles: [");
    for (int r=0; r<tree->info->nrole; ++r) {
      printf(" %s", tree->info->roles[r]->name);
      for (int p=0; p<tree->info->roles[r]->dimen; ++p) {
        printf("[");
        st_expr_print(tree->info->roles[r]->param[p]);
        printf("]");
      }
    }
    printf(" ]\n");

    printf("Groups: [");
    for (int g=0; g<tree->info->ngroup; ++g) {
      printf(" %s={", tree->info->groups[g]->name);
      for (int r=0; r<tree->info->groups[g]->nmemb; ++r) {
        printf(" %s", tree->info->groups[g]->membs[r]->name);
        for (int p=0; p<tree->info->groups[g]->membs[r]->dimen; ++p) {
          printf("[");
          st_expr_print(tree->info->groups[g]->membs[r]->param[p]);
          printf("]");
        }
      }
      printf("}");
    }
    printf(" ]\n");
  } else {
    printf("Protocol info not found\n");
  }

  printf("--------------------\n");

  if (tree->root != NULL) {
    st_node_print_r(tree->root, 0);
  } else {
    printf("Protocol tree is empty\n");
  }

  printf("--------------------\n\n");
}


void st_node_print_r(const st_node *node, int indent)
{
  int i;

  st_node_print(node, indent);
  for (i=0; i<node->nchild; ++i) {
    st_node_print_r(node->children[i], indent+1);
  }
}


void st_node_print(const st_node *node, int indent)
{
  int i;

  if (node != NULL) {
    if (node->marked) {
      printf("%3d *>", indent);
    } else {
      printf("%3d | ", indent);
    }
    for (i=indent; i>0; --i) printf("  ");
    switch (node->type) {

      case ST_NODE_ROOT: // ---------- ROOT ----------
        printf("Node { type: root }\n");
        break;

      case ST_NODE_SENDRECV: // ---------- SENDRECV ----------

        printf("Node { type: interaction, from: %s", node->interaction->from->name);
        for (int j=0; j<node->interaction->from->dimen; ++j) {
          printf("[");
          st_expr_print(node->interaction->from->param[j]);
          printf("]");
        }

        printf(", to(%d): ", node->interaction->nto);
        printf("[%s", node->interaction->to[0]->name);
        for (int j=0; j<node->interaction->to[0]->dimen; ++j) {
          printf("[");
          st_expr_print(node->interaction->to[0]->param[j]);
          printf("]");
        }
        printf(" ..]");

        printf(", msgsig: { op: %s, payload: %s }", node->interaction->msgsig.op, node->interaction->msgsig.payload);

        printf("}\n");
        break;

      case ST_NODE_SEND: // ---------- SEND ----------
        printf("Node { type: send");
        printf(", to(%d): ", node->interaction->nto);
        printf("[%s", node->interaction->to[0]->name);
        for (int j=0; j<node->interaction->to[0]->dimen; ++j) {
          printf("[");
          st_expr_print(node->interaction->to[0]->param[j]);
          printf("]");
        }
        printf(" ..]");

        printf(", msgsig: { op: %s, payload: %s }", node->interaction->msgsig.op, node->interaction->msgsig.payload);

        if (NULL != node->interaction->msg_cond) {
          printf(", cond: %s", node->interaction->msg_cond->name);
          for (int r=0; r<node->interaction->msg_cond->dimen; ++r) {
            printf("[");
            st_expr_print(node->interaction->msg_cond->param[r]);
            printf("]");
          }
        } // if msg_cond

        printf("}\n");
        break;

      case ST_NODE_RECV: // ----------- RECV -----------
        printf("Node { type: recv, from: %s", node->interaction->from->name);
        for (int j=0; j<node->interaction->from->dimen; ++j) {
          printf("[");
          st_expr_print(node->interaction->from->param[j]);
          printf("]");
        }

        printf(", msgsig: { op: %s, payload: %s }", node->interaction->msgsig.op, node->interaction->msgsig.payload);

        if (NULL != node->interaction->msg_cond) {
          printf(", cond: %s", node->interaction->msg_cond->name);
          for (int r=0; r<node->interaction->msg_cond->dimen; ++r) {
            printf("[");
            st_expr_print(node->interaction->msg_cond->param[r]);
            printf("]");
          }
        } // if msg_cond

        printf("}\n");
        break;

      case ST_NODE_CHOICE: // ---------- CHOICE ----------
        printf("Node { type: choice, at: %s ", node->choice->at->name);
        for (int p=0; p<node->choice->at->dimen; ++p) {
          printf("[");
          st_expr_print(node->choice->at->param[p]);
          printf("]");
        }
        printf("} %d children \n", node->nchild);
        break;

      case ST_NODE_PARALLEL: // ---------- PARALLEL ----------
        printf("Node { type: par }\n");
        break;

      case ST_NODE_RECUR: // ---------- RECUR ----------
        printf("Node { type: recur, label: %s }\n", node->recur->label);
        break;

      case ST_NODE_CONTINUE: // ---------- CONTINUE ----------
        printf("Node { type: continue, label: %s }\n", node->cont->label);
        break;

      case ST_NODE_FOR: // ---------- FOR ----------
        printf("Node { type: forloop, var: %s, range: ", node->forloop->range->bindvar);
        st_expr_print(node->forloop->range->from);
        printf("..");
        st_expr_print(node->forloop->range->to);
        if (node->forloop->except != NULL) printf(", except: %s ", node->forloop->except);
        printf("}\n");
        break;

      case ST_NODE_ALLREDUCE: // ---------- ALLREDUCE ----------
        printf("Node { type: allreduce, ");
        printf(", msgsig: { op: %s, payload: %s } }\n", node->allreduce->msgsig.op, node->allreduce->msgsig.payload);
        break;

      case ST_NODE_ONEOF: // ---------- ONEOF ----------
        printf("Node { %stype: oneof, role: %s, range: ", (node->oneof->unordered ? "unordered " : ""), node->oneof->role);
        st_expr_print(node->oneof->range->from);
        printf("..");
        st_expr_print(node->oneof->range->to);
        printf("}\n");
        break;

      case ST_NODE_IFBLK: // ---------- IFBLK ----------
        assert(node->ifblk->cond != NULL);
        printf("Node { type: if block, cond: "/*, node->ifblk->cond->name*/);
        for (int j=0; j<node->ifblk->cond->dimen; ++j) {
          printf("[");
          st_expr_print(node->ifblk->cond->param[j]);
          printf("]");
        }
        printf(" }\n");
        break;

      default:
        fprintf(stderr, "%s:%d %s Unknown node type: %d\n", __FILE__, __LINE__, __FUNCTION__, node->type);
        break;
    }
  }
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


int st_node_compare_async(const st_node *node, const st_node *other)
{
  int identical = 1;
  int search_from, search_to;
  int visited[node->nchild];

  int i, j;

  // We currently only support async optimisation inside recursion blocks
  // and only in the toplevel child of a recursion block
  //
  if ((node->type != ST_NODE_FOR && node->type != ST_NODE_RECUR) || (node->type != ST_NODE_FOR && other->type != ST_NODE_RECUR))
    return 0;

  if (node->nchild != other->nchild)
    return 0;

  for (i=0; i<node->nchild; ++i) {
    visited[i] = 0;
  }

  // If first node is not send/recv, used ordinary compare
  if (node->nchild > 0 && node->children[0]->type != ST_NODE_SEND && node->children[0]->type != ST_NODE_RECV) {

    for (i=0; i<node->nchild; ++i) {
      identical &= st_node_compare_r(node->children[i], other->children[i]);
    }

  } else {

    // Mark range of consecutive send/recv for async optimisation (search_from - search_to).
    search_from = 0;
    search_to   = node->nchild;

    for (i=0; i<node->nchild; ++i) {
      if (ST_NODE_SEND == node->children[i]->type || ST_NODE_RECV == node->children[i]->type) {
        search_from = i;
        for (j=i+1; j<node->nchild; ++j) {
          if (ST_NODE_SEND != node->children[j]->type && ST_NODE_RECV != node->children[j]->type) {
            search_to = j;
            break;
          }
        }
        // If nothing is found, search_to is node->nchild;
        break; // CHANGEME: We consider the first segment only
      }
    }

    printf("%s: Matching range %d - %d\n", __FUNCTION__, search_from, search_to-1);
    st_node_print(node->children[search_from], 0);
    st_node_print(node->children[search_to-1], 0);

    // The actual matching.
    for (i=search_from; i<search_to; ++i) {
      //assert(ST_NODE_SEND == node->children[i]->type || ST_NODE_RECV == node->children[i]->type);

      if (ST_NODE_RECV == node->children[i]->type) {
        // - Look for matching receive
        // - Allow send in same channel (to overtake)
        // - Stop at non-matching receive in same channel or end of search range
        for (j=search_from; j<search_to; ++j) {

          // Case 0: This node has been matched previously.
          if (visited[j] == 1) {
            continue;
          }

          // Case 1: RECV in the same channel.
          if (visited[j] == 0
              && ST_NODE_RECV == other->children[j]->type) { // Recv node

            if (st_node_compare_interaction(node->children[i], other->children[j])) {
              // Matching RECV node
              printf("RECV matched a RECV node: %d-%d: Done\n", i, j);
              st_node_print(node->children[i], 0);
              st_node_print(other->children[j], 0);
              visited[j] = 1;
              identical &= 1;
              break;
            } else if (st_node_is_overlapped(node->children[i], other->children[j])) {
              // Don't allow RECV-RECV overtake in same channel
              node->children[i]->marked = 1;
              other->children[j]->marked = 1;
              identical = 0;
              break;
            } else { // Not the same and not overlapped
              continue;
            }
          }

          // Case 2: SEND in same channel.
          if (visited[j] == 0
              && ST_NODE_SEND == other->children[j]->type
              && st_node_is_overlapped(node->children[i], other->children[j])) { // Send node
            // Same channel SEND is allowed.
            printf("RECV matched a SEND node: %d-%d: Skip\n", i, j);
            st_node_print(node->children[i], 0);
            st_node_print(other->children[j], 0);
            continue;
          }

        } // for nodes matching RECV

        // No matching node found
        if (j == search_to) {
          node->children[i]->marked = 1;
          identical = 0;
        }

      } else if (ST_NODE_SEND == node->children[i]->type) {
        // - Look for matching send
        // - Allow send in the same channel (to overtake)
        // - Stop at receive in the same channel or end of search range
        for (j=search_from; j<search_to; ++j) {

          // Case 0: This node has been matched previously.
          if (visited[j] == 1) {
            continue;
          }

          // Case 1: SEND in the same channel.
          if (visited[j] == 0
              && ST_NODE_SEND == other->children[j]->type) {
            if (st_node_compare_interaction(node->children[i], other->children[j])) {
              // Matching SEND node
              printf("SEND matched a SEND node: %d-%d: Done\n", i, j);
              st_node_print(node->children[i], 0);
              st_node_print(other->children[j], 0);
              visited[j] = 1;
              identical &= 1;
              break;
            } else if (st_node_is_overlapped(node->children[i], other->children[j])) {
              // Don't allow SEND-SEND overtake in same channel
              printf("SEND unmatched a SEND node: %d-%d: Wrong\n", i, j);
              st_node_print(node->children[i], 0);
              st_node_print(other->children[j], 0);
              node->children[i]->marked = 1;
              other->children[j]->marked = 1;
              identical = 0;
              break;
            } else { // Not the same and not overlapped
              continue;
            }
          }

          // Case 2: RECV node in same channel
          if (visited[j] == 0
              && ST_NODE_RECV == other->children[j]->type
              && st_node_is_overlapped(node->children[i], other->children[j])) {
            // Don't allow RECV-SEND overtake in the same channel
            printf("SEND matched a RECV node: %d-%d: Wrong\n", i, j);
            st_node_print(node->children[i], 0);
            st_node_print(other->children[j], 0);
            node->children[i]->marked = 1;
            other->children[j]->marked = 1;
            identical = 0;
            break;
          }

        } // for nodes matching SEND

        // No matching node found
        if (j == search_to) {
          node->children[i]->marked = 1;
          identical = 0;
        }

      }

    } // Checking done for search_from - search_to

    printf("%s: Matching range (non async) %d - %d\n", __FUNCTION__, search_to, node->nchild-1);
    st_node_print(node->children[search_from], 0);
    st_node_print(other->children[search_to-1], 0);


    for (i=search_to; i<node->nchild; ++i) {
      identical &= st_node_compare_r(node->children[i], other->children[i]);
    }
  }

  return identical;
}


int st_node_compare_r(st_node *node, st_node *other)
{
  int identical = 1;
  int i;

  if (node != NULL && other != NULL) {
    identical &= st_node_compare(node, other);

    if (node->type == ST_NODE_RECUR || node->type == ST_NODE_FOR) {
      identical &= st_node_compare_async(node, other);
    } else {
      for (i=0; i<node->nchild; ++i) {
        identical &= st_node_compare_r(node->children[i], other->children[i]);
      }
    }
  }

  return identical;
}


int st_node_compare_msgsig(const st_node_msgsig_t msgsig, const st_node_msgsig_t other)
{
  return ( !((msgsig.op == NULL && other.op != NULL) || (msgsig.op != NULL && other.op == NULL))
           && ((msgsig.op == NULL && other.op == NULL) || 0 == strcmp(msgsig.op, other.op))
           && (0 == strcmp(msgsig.payload, other.payload)) );
}


// Helper function to compare interaction nodes or ranges of interaction nodes
int st_node_compare_interaction(st_node *node, st_node *other)
{
  int identical = 1;
  int i = 0;
  assert(ST_NODE_SENDRECV == node->type || ST_NODE_SEND == node->type || ST_NODE_RECV == node->type);
  if (node->interaction->msg_cond != NULL && other->interaction->msg_cond != NULL) {
    identical &= (node->interaction->msg_cond->dimen == other->interaction->msg_cond->dimen);
    for (int j=0; j<node->interaction->msg_cond->dimen || !identical; ++j) {
      identical &= st_expr_is_identical(node->interaction->msg_cond->param[j], other->interaction->msg_cond->param[j]);
    }
  }

  switch (node->type) {
    case ST_NODE_SENDRECV:
      // Send
      for (i=0; i<node->interaction->nto; ++i) {
        identical &= (0 == strcmp(node->interaction->to[i]->name, other->interaction->to[i]->name) || 0 == strcmp(other->interaction->to[i]->name, "__ROLE__"));
        identical &= (node->interaction->to[i]->dimen == other->interaction->to[i]->dimen);
        for (int j=0; j<node->interaction->to[i]->dimen || !identical; ++j) {
          identical &= st_expr_is_identical(node->interaction->to[i]->param[j], other->interaction->to[i]->param[j]);
        }
      }
      // Receive
      identical &= (0 == strcmp(node->interaction->from->name, other->interaction->from->name) || 0 == strcmp(other->interaction->from->name, "__ROLE__"));
        identical &= (node->interaction->from->dimen == other->interaction->from->dimen);
        for (int j=0; j<node->interaction->from->dimen || !identical; ++j) {
          identical &= st_expr_is_identical(node->interaction->from->param[j], other->interaction->from->param[j]);
        }
      break;

    case ST_NODE_SEND:
      for (i=0; i<node->interaction->nto; ++i) {
        identical &= (0 == strcmp(node->interaction->to[i]->name, other->interaction->to[i]->name) || 0 == strcmp(other->interaction->to[i]->name, "__ROLE__"));
        identical &= (node->interaction->to[i]->dimen == other->interaction->to[i]->dimen);
        for (int j=0; j<node->interaction->to[i]->dimen || !identical; ++j) {
          identical &= st_expr_is_identical(node->interaction->to[i]->param[j], other->interaction->to[i]->param[j]);
        }
      }
      break;

    case ST_NODE_RECV:
      identical &= (0 == strcmp(node->interaction->from->name, other->interaction->from->name) || 0 == strcmp(other->interaction->from->name, "__ROLE__"));
      identical &= (node->interaction->from->dimen == other->interaction->from->dimen);
      for (int j=0; j<node->interaction->from->dimen || !identical; ++j) {
        identical &= st_expr_is_identical(node->interaction->from->param[j], other->interaction->from->param[j]);
      }
      break;

    default:
      fprintf(stderr, "%s:%d %s Unknown node type: %d\n", __FILE__, __LINE__, __FUNCTION__, node->type);
  }

  return identical;
}


int st_node_compare(st_node *node, st_node *other)
{
  int identical = 1;
  if (node != NULL && other != NULL) {
    identical = (node->type == other->type && node->nchild == other->nchild);

    if (identical) {

      switch (node->type) {
        case ST_NODE_ROOT:
          break;

        case ST_NODE_SENDRECV:
          identical &= st_node_compare_msgsig(node->interaction->msgsig, other->interaction->msgsig);
          identical &= st_node_compare_interaction(node, other);
          break;

        case ST_NODE_SEND:
          identical &= st_node_compare_msgsig(node->interaction->msgsig, other->interaction->msgsig);
          identical &= st_node_compare_interaction(node, other);
          break;

        case ST_NODE_RECV:
          identical &= st_node_compare_msgsig(node->interaction->msgsig, other->interaction->msgsig);
          identical &= st_node_compare_interaction(node, other);
          break;

        case ST_NODE_CHOICE:
          identical &= (0 == strcmp(node->choice->at->name, other->choice->at->name));
          // TODO compare params
          break;

        case ST_NODE_PARALLEL:
          break;

        case ST_NODE_RECUR:
          // The label might be different: source code recursion label are generated
          // identical &= (0 == strcmp(node->recur->label, other->recur->label));
          break;

        case ST_NODE_CONTINUE:
          // The label might be different: source code continue label are generated
          // identical &= (0 == strcmp(node->cont->label, other->cont->label));
          break;

        case ST_NODE_FOR:
          identical &= (0 == strcmp(node->forloop->range->bindvar, other->forloop->range->bindvar));
          identical &= st_expr_is_identical(node->forloop->range->from, other->forloop->range->from);
          identical &= st_expr_is_identical(node->forloop->range->to, other->forloop->range->to);
          break;

        case ST_NODE_ALLREDUCE:
          identical &= st_node_compare_msgsig(node->allreduce->msgsig, other->allreduce->msgsig);
          break;

        case ST_NODE_IFBLK:
          identical &= (0 == strcmp(node->ifblk->cond->name, other->ifblk->cond->name));
          identical &= (node->ifblk->cond->dimen == other->ifblk->cond->dimen);
          for (int j=0; j<node->ifblk->cond->dimen || !identical; ++j) {
            identical &= st_expr_is_identical(node->ifblk->cond->param[j], other->ifblk->cond->param[j]);
          }
          break;

        case ST_NODE_ONEOF:
          identical &= (0 == strcmp(node->oneof->range->bindvar, other->oneof->range->bindvar));
          identical &= st_expr_is_identical(node->oneof->range->from, other->oneof->range->from);
          identical &= st_expr_is_identical(node->oneof->range->to, other->oneof->range->to);
          break;

        default:
          fprintf(stderr, "%s:%d %s Unknown node type: %d\n", __FILE__, __LINE__, __FUNCTION__, node->type);
          break;
      }

    } // if identical

    if (!identical) {
      node->marked = 1;
      other->marked = 1;
    }

  }
  return identical;
}

int st_node_is_overlapped(st_node *node, st_node *other)
{
  return 0;
}

st_role *st_node_copy_role(const st_role *role)
{
  if (role == NULL) {
    return NULL;
  }

  st_role *newrole = (st_role *)malloc(sizeof(st_role));
  newrole->name = strdup(role->name);
  newrole->dimen = role->dimen;
  newrole->param = (st_expr **)calloc(newrole->dimen, sizeof(st_expr *));
  for (int i=0; i<newrole->dimen; ++i) {
    newrole->param[i] = st_expr_copy(role->param[i]);
  }

  return newrole;
}


