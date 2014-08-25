/**
 * \file
 * This file contains functions to compare two session nodes.
 *
 * \headerfile "sesstype/st_node.h"
 * \headerfile "sesstype/st_node_print.h"
 * \headerfile "sesstype/st_expr.h"
 */

#include <assert.h>
#include <string.h>
#include "sesstype/st_node.h"
#include "sesstype/st_node_print.h"
#include "sesstype/st_expr.h"


int st_node_compare_async(const st_node *node, const st_node *other)
{
  int identical = 1;
  int search_from, search_to;
  int visited[node->nchild];

  int i, j;

  // We currently only support async optimisation inside recursion blocks
  // and only in the toplevel child of a recursion block
  //
  if (   (node->type != ST_NODE_FOR && node->type != ST_NODE_RECUR)
      || (other->type != ST_NODE_FOR && other->type != ST_NODE_RECUR))
    return 0;

  if (node->nchild != other->nchild)
    return 0;

  memset(visited, 0, node->nchild * sizeof(int));

  // If first node is not send/recv, used ordinary compare
  if (   node->nchild > 0
      && node->children[0]->type != ST_NODE_SEND
      && node->children[0]->type != ST_NODE_RECV) {

    for (i=0; i<node->nchild; ++i) {
      identical &= st_node_compare_r(node->children[i], other->children[i]);
    }

  } else {

    // Mark range of consecutive send/recv for async optimisation (search_from - search_to).
    search_from = 0;
    search_to   = node->nchild;

    for (i=0; i<node->nchild; ++i) {
      if (   ST_NODE_SEND == node->children[i]->type
          || ST_NODE_RECV == node->children[i]->type) {
        search_from = i;
        for (j=i+1; j<node->nchild; ++j) {
          if (   ST_NODE_SEND != node->children[j]->type
              && ST_NODE_RECV != node->children[j]->type) {
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
  int cmp = (   (msgsig.op == NULL || other.op != NULL)
             && (msgsig.op != NULL || other.op == NULL)
             && ((msgsig.op != NULL && 0 == strcmp(msgsig.op, other.op)) || msgsig.op == NULL)
             && (msgsig.npayload == other.npayload));

  for (int pl=0; cmp && pl<msgsig.npayload; pl++) {
    cmp &= (st_expr_is_identical(msgsig.payloads[pl].expr, other.payloads[pl].expr)
            && 0 == strcmp(msgsig.payloads[pl].name, other.payloads[pl].name)
            && 0 == strcmp(msgsig.payloads[pl].type, other.payloads[pl].type));
  }
  return cmp;
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
#ifdef PABBLE_DYNAMIC
        case ST_NODE_ONEOF:
          identical &= (0 == strcmp(node->oneof->range->bindvar, other->oneof->range->bindvar));
          identical &= st_expr_is_identical(node->oneof->range->from, other->oneof->range->from);
          identical &= st_expr_is_identical(node->oneof->range->to, other->oneof->range->to);
          break;
#endif

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
