#ifndef SESSTYPE__ST_NODE_PRINT__H__
#define SESSTYPE__ST_NODE_PRINT__H__
/**
 * \file
 * Thie file contains the tree representation of (multiparty) session
 * according to the Scribble language specification and provides functions
 * to print session type trees.
 *
 */

#include <stdio.h>

#include "sesstype/st_node.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Print a st_tree with meta information.
 * 
 * @param[in] tree Tree to print.
 */
void st_tree_print(const st_tree *tree);


/**
 * \brief Print a single st_node.
 *
 * @param[in] node   Node to print.
 * @param[in] indent Indentation (number of spaces).
 */
void st_node_print(const st_node *node, int indent);


/**
 * \brief Print a single st_node and all its children recursively.
 *
 * @param[in] node   Node to print.
 * @param[in] indent Indentation (number of spaces).
 */
void st_node_print_r(const st_node *node, int indent);


/**
 * \brief Print a single st_node and all its children recursively to given
 * output stream.
 *
 * @param[out] stream Output stream.
 * @param[in]  node   Node to print.
 * @param[in]  indent Indentation (number of spaces).
 */
void st_node_fprint_r(FILE *stream, const st_node *node, int indent);


/**
 * \brief Print a single st_node to given output stream.
 *
 * @param[out] stream Output stream.
 * @param[in]  node   Node to print.
 * @param[in]  indent Indentation (number of spaces).
 */
void st_node_fprint(FILE *stream, const st_node *node, int indent);


void st_role_fprint(FILE *stream, const st_role *role);
void st_node_msgsig_fprint(FILE *stream, const st_node_msgsig_t msgsig);


void st_node_fprint_root(FILE *stream, const st_node *node);
void st_node_fprint_sendrecv(FILE *stream, const st_node *node);
void st_node_fprint_send(FILE *stream, const st_node *node);
void st_node_fprint_recv(FILE *stream, const st_node *node);
void st_node_fprint_choice(FILE *stream, const st_node *node);
void st_node_fprint_parallel(FILE *stream, const st_node *node);
void st_node_fprint_recur(FILE *stream, const st_node *node);
void st_node_fprint_continue(FILE *stream, const st_node *node);
void st_node_fprint_for(FILE *stream, const st_node *node);
void st_node_fprint_allreduce(FILE *stream, const st_node *node);
#ifdef PABBLE_DYNAMIC
void st_node_fprint_oneof(FILE *stream, const st_node *node);
#endif
void st_node_fprint_ifblk(FILE *stream, const st_node *node);

#ifdef __cplusplus
}
#endif

#endif // SESSTYPE__ST_NODE_PRINT__H__
