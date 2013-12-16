/**
 * \file
 * This file contains functinos to print the tree representation of (multiparty)
 * session and.
 *
 * \headerfile "sesstype/st_node.h"
 * \headerfile "sesstype/st_node_print.h"
 * \headerfile "sesstype/st_expr.h"
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "sesstype/st_node.h"
#include "sesstype/st_node_print.h"
#include "sesstype/st_expr.h"


void st_tree_print(const st_tree *tree)
{
  if (tree == NULL) {
    fprintf(stderr, "%s:%d %s tree is NULL\n", __FILE__, __LINE__, __FUNCTION__);
  }

  printf("\n-------Summary------\n");

  if (tree->info != NULL) {
    printf("Protocol: %s#%s\n", tree->info->module, tree->info->name);
    switch (tree->info->type) {
      case ST_TYPE_GLOBAL: printf("Global protocol\n"); break;
      case ST_TYPE_LOCAL:  printf("Local protocol\n");  break;
      default:
        assert(0/* Unrecognised Type*/);
    }

    if (ST_TYPE_GLOBAL != tree->info->type) {
      if (tree->info->myrole != NULL) {
        printf("Endpoint role: ");
        st_role_fprint(stdout, tree->info->myrole);
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
      if (r!=0) printf(", ");
      st_role_fprint(stdout, tree->info->roles[r]);
    }
    printf("]\n");

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


inline void st_node_print(const st_node *node, int indent)
{
  st_node_fprint(stdout, node, indent);
}


inline void st_node_print_r(const st_node *node, int indent)
{
  st_node_fprint_r(stdout, node, indent);
}


void st_node_fprint(FILE *stream, const st_node *node, int indent)
{
  assert(node != NULL);

  fprintf(stream, "%3d %s%*s", indent, node->marked ? "*>" : "| ", indent, "  ");

  switch(node->type) {
    case ST_NODE_ROOT:      st_node_fprint_root(stream, node);      break;
    case ST_NODE_SENDRECV:  st_node_fprint_sendrecv(stream, node);  break;
    case ST_NODE_SEND:      st_node_fprint_send(stream, node);      break;
    case ST_NODE_RECV:      st_node_fprint_recv(stream, node);      break;
    case ST_NODE_CHOICE:    st_node_fprint_choice(stream, node);    break;
    case ST_NODE_PARALLEL:  st_node_fprint_parallel(stream, node);  break;
    case ST_NODE_RECUR:     st_node_fprint_recur(stream, node);     break;
    case ST_NODE_CONTINUE:  st_node_fprint_continue(stream, node);  break;
    case ST_NODE_FOR:       st_node_fprint_for(stream, node);       break;
    case ST_NODE_ALLREDUCE: st_node_fprint_allreduce(stream, node); break;
    case ST_NODE_ONEOF:     st_node_fprint_oneof(stream, node);     break;
    case ST_NODE_IFBLK:     st_node_fprint_ifblk(stream, node);     break;
    default:
      fprintf(stderr, "%s:%d %s Unknown node type: %d\n", __FILE__, __LINE__, __FUNCTION__, node->type);
      break;
  }
}


void st_node_fprint_r(FILE *stream, const st_node *node, int indent)
{
  st_node_fprint(stream, node, indent);
  for (int i=0; i<node->nchild; ++i) {
    st_node_fprint_r(stream, node->children[i], indent+1);
  }
}


void st_role_fprint(FILE *stream, const st_role *role)
{
  assert(role != NULL);
  fprintf(stream, "%s", role->name);
  for (int dimen=0; dimen<role->dimen; ++dimen) {
    fprintf(stream, "[");
    st_expr_fprint(stream, role->param[dimen]);
    fprintf(stream, "]");
  }
}


inline void st_node_msgsig_fprint(FILE *stream, const st_node_msgsig_t msgsig)
{
  assert(msgsig.op != NULL);
  assert(msgsig.payload != NULL);
  fprintf(stream, "msgsig: { op: %s, payload: %s }", msgsig.op, msgsig.payload);
}


inline void st_node_fprint_root(FILE *stream, const st_node *node)
{
  assert(node != NULL && node->type == ST_NODE_ROOT);
  fprintf(stream, "Node { type: root }\n");
}


inline void st_node_fprint_sendrecv(FILE *stream, const st_node *node)
{
  assert(node != NULL && node->type == ST_NODE_SENDRECV);

  fprintf(stream, "Node { type: interaction, from: ");
  st_role_fprint(stream, node->interaction->from);

  fprintf(stream, ", to(%d): [", node->interaction->nto);
  st_role_fprint(stream, node->interaction->to[0]);
  if (node->interaction->nto > 1) fprintf(stream, ", ..");
  fprintf(stream, "], ");

  st_node_msgsig_fprint(stream, node->interaction->msgsig);

  fprintf(stream, "}\n");
}


inline void st_node_fprint_send(FILE *stream, const st_node *node)
{
  assert(node != NULL && node->type == ST_NODE_SEND);

  fprintf(stream, "Node { type: send, to(%d): [", node->interaction->nto);
  st_role_fprint(stream, node->interaction->to[0]);
  if (node->interaction->nto > 1) fprintf(stream, ", ..");
  fprintf(stream, "], ");

  st_node_msgsig_fprint(stream, node->interaction->msgsig);

  if (node->interaction->msg_cond != NULL) {
    fprintf(stream, ", cond: ");
    st_role_fprint(stream, node->interaction->msg_cond);
  } // if msg_cond

  fprintf(stream, "}\n");
}


inline void st_node_fprint_recv(FILE *stream, const st_node *node)
{
  assert(node != NULL && node->type == ST_NODE_RECV);

  fprintf(stream, "Node { type: recv, from: ");
  st_role_fprint(stream, node->interaction->from);

  fprintf(stream, ", ");
  st_node_msgsig_fprint(stream, node->interaction->msgsig);

  if (node->interaction->msg_cond != NULL) {
    fprintf(stream, ", cond: ");
    st_role_fprint(stream, node->interaction->msg_cond);
  } // if msg_cond

  fprintf(stream, "}\n");
}


inline void st_node_fprint_choice(FILE *stream, const st_node *node)
{
  assert(node != NULL && node->type == ST_NODE_CHOICE);

  fprintf(stream, "Node { type: choice, at: ");
  st_role_fprint(stream, node->choice->at);

  fprintf(stream, "} %d children \n", node->nchild);
}


inline void st_node_fprint_parallel(FILE *stream, const st_node *node)
{
  assert(node != NULL && node->type == ST_NODE_PARALLEL);

  fprintf(stream, "Node { type: par }\n");
}


inline void st_node_fprint_recur(FILE *stream, const st_node *node)
{
  assert(node != NULL && node->type == ST_NODE_RECUR);

  fprintf(stream, "Node { type: recur, label: %s }\n", node->recur->label);
}


inline void st_node_fprint_continue(FILE *stream, const st_node *node)
{
  assert(node != NULL && node->type == ST_NODE_CONTINUE);
  fprintf(stream, "Node { type: continue, label: %s }\n", node->cont->label);
}


inline void st_node_fprint_for(FILE *stream, const st_node *node)
{
  assert(node != NULL && node->type == ST_NODE_FOR);

  fprintf(stream, "Node { type: forloop, var: %s, range: ", node->forloop->range->bindvar);
  st_expr_fprint(stream, node->forloop->range->from);
  fprintf(stream, "..");
  st_expr_fprint(stream, node->forloop->range->to);
  if (node->forloop->except != NULL) fprintf(stream, ", except: %s ", node->forloop->except);

  fprintf(stream, "}\n");
}


inline void st_node_fprint_allreduce(FILE *stream, const st_node *node)
{
  assert(node != NULL && node->type == ST_NODE_ALLREDUCE);

  fprintf(stream, "Node { type: allreduce, ");
  fprintf(stream, ", ");
  st_node_msgsig_fprint(stream, node->allreduce->msgsig);

  fprintf(stream, "}\n");
}


inline void st_node_fprint_oneof(FILE *stream, const st_node *node)
{
  assert(node != NULL && node->type == ST_NODE_ONEOF);

  fprintf(stream, "Node { %stype: oneof, role: %s, range: ", (node->oneof->unordered ? "unordered " : ""), node->oneof->role);
  st_expr_fprint(stream, node->oneof->range->from);
  fprintf(stream, "..");
  st_expr_fprint(stream, node->oneof->range->to);

  fprintf(stream, "}\n");
}


inline void st_node_fprint_ifblk(FILE *stream, const st_node *node)
{
  assert(node != NULL && node->type == ST_NODE_IFBLK);

  fprintf(stream, "Node { type: if block, cond: ");
  st_role_fprint(stream, node->ifblk->cond);
  fprintf(stream, "}\n");
}
