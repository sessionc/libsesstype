#ifndef SESSTYPE__ST_NODE__H__
#define SESSTYPE__ST_NODE__H__
/**
 * @file
 * Thie file contains the tree representation of (multiparty) session
 * according to the Scribble language specification and provides functions
 * to build and manipulate session type trees.
 *
 */

#include <stdio.h>
#include "sesstype/st_expr.h"
#include "sesstype/st_role.h"
#include "sesstype/st_role_group.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ST_NODE_ROOT      0
#define ST_NODE_SENDRECV  1
#define ST_NODE_CHOICE    2
#define ST_NODE_PARALLEL  3
#define ST_NODE_RECUR     4
#define ST_NODE_CONTINUE  5
#define ST_NODE_FOR       6
#define ST_NODE_ALLREDUCE 7
#ifdef PABBLE_DYNAMIC
#define ST_NODE_ONEOF     8
#endif

// Endpoint only.
#define ST_NODE_SEND      9
#define ST_NODE_RECV      10
#define ST_NODE_IFBLK     11

#define ST_TREE_LOCAL     0x80  // 128
#define ST_TREE_GLOBAL    0x100 // 256

#define ST_CONST_VALUE 1 // Constant defined as value
#define ST_CONST_BOUND 2 // Constant defined as ower/upper bounds
#define ST_CONST_INF   3 // Constant defined as lbound/inf upper bound


/**
 * Import.
 */
typedef struct {
  char *name;
  char *as;
  char *from;
} st_tree_import_t;


/**
 * Message payloads.
 */
typedef struct {
  char *name;    /**< Payload annotation name. */
  char *type;    /** <Payload type name. */
  st_expr *expr; /**< Payload expression. */
} st_node_msgsig_payload_t;


/**
 * Message signature.
 */
typedef struct {
  char *op;                           /**< Label or operator. */
  unsigned int npayload;              /**< Number of payload. */
  st_node_msgsig_payload_t *payloads; /**< List of payloads. */
} st_node_msgsig_t;


typedef st_role msg_cond_t;


/**
 * Interaction (message passing).
 */
typedef struct {
  st_node_msgsig_t msgsig; /**< Message signature. */

  int nto;                 /**< Number of Senders. */
  st_role **to;            /**< List [role] of Receivers. */
  st_role *from;           /**< Sender. */

  msg_cond_t *msg_cond;    /**< Pattern matching condition. */
} st_node_interaction_t;


/**
 * Recursion.
 */
typedef struct {
  char *label; /**< Recursion label. */
} st_node_recur_t;


/**
 * Continue.
 */
typedef struct {
  char *label; /**< Target recursion label. */
} st_node_continue_t;


/**
 * Choice.
 */
typedef struct {
  st_role *at;
} st_node_choice_t;


/**
 * Foreach loop.
 */
typedef struct {
  st_rng_expr_t *range; /**< Binding range. */
  char *except;
} st_node_for_t;


/**
 * Allreduce.
 */
typedef struct {
  st_node_msgsig_t msgsig;
} st_node_allreduce_t;


/**
 * If (block-level).
 */
typedef struct {
  msg_cond_t *cond;
} st_node_ifblk_t;

#ifdef PABBLE_DYNAMIC
/**
 * Existential operator.
 */
typedef struct {
  char *role;
  st_rng_expr_t *range;
  unsigned int unordered;
} st_node_oneof_t;
#endif


struct __st_node {
  int type;

  union {
    st_node_interaction_t *interaction;
    st_node_choice_t      *choice;
    st_node_recur_t       *recur;
    st_node_continue_t    *cont;
    st_node_for_t         *forloop;
    st_node_allreduce_t   *allreduce;
    st_node_ifblk_t       *ifblk;
#ifdef PABBLE_DYNAMIC
    st_node_oneof_t       *oneof;
#endif
  };

  int nchild;
  struct __st_node **children;
  int marked;
};

/**
 * Constants.
 */
typedef struct {
  const char *name;
  int type;
  union {
    unsigned int value;
    struct {
      unsigned int lbound;
      unsigned int ubound;
    } bounds;
    struct {
      unsigned int lbound;
    } inf; // ST_CONST_INF (Infinity upper bound)
  };
} st_const_t;


/**
 * Session type tree metadata.
 */
typedef struct {
  int nimport;
  st_tree_import_t **imports;
  int nconst;
  st_const_t **consts;

  int type;                /**< Session Tree type: global/local/parametrised-local */

  char *name;        /**< Protocol name. */
  st_role *myrole;         /**< Projected Role. */

  // Role declarations.
  int nrole;               /**< Number of Roles. */ 
  st_role **roles;         /**< List of Roles. */
  int ngroup;              /**< Number of Groups. */
  st_role_group **groups;  /**< List of Groups. */
  char *module;      /**< Full module/package name of protocol. */
} st_info;


/**
 * Session type tree node representation.
 */
typedef struct __st_node st_node;


/**
 * Session type tree represenation.
 */
typedef struct {
  st_info *info; /**< Protocol metadata. */
  st_node *root; /**< Protocol body. */
} st_tree;


/**
 * @brief Initialise session type tree.
 *
 * @param[in,out] tree Tree to initialise.
 *
 * @returns Initialised tree.
 */
st_tree *st_tree_init(st_tree *tree);


/**
 * @brief Cleanup session type tree.
 *
 * @param[in,out] tree Tree to free.
 */
void st_tree_free(st_tree *tree);


/**
 * @brief Cleanup session type node (recursive).
 *
 * @param[in,out] node Node to free.
 */
void st_node_free(st_node *node);


/**
 * @brief Set module name of protocol.
 * If module is not set, the default module name is 'default'.
 *
 * @param[in,out] tree Session type tree of protocol.
 * @param[in]     module Module name of protocol.
 */
st_tree *st_tree_set_module(st_tree *tree, char const *module);


/**
 * @brief Set name of protocol.
 *
 * @param[in,out] tree Session type tree of protocol.
 * @param[in]     name Name of protocol.
 */
st_tree *st_tree_set_name(st_tree *tree, char const *name);


/**
 * @brief Set name of protocol (with role parameters).
 *
 * @param[in,out] tree Session type tree of protocol.
 * @param[in]     name Name of protocol
 * @param[in]     role Role of protocol.
 */
st_tree *st_tree_set_local_name(st_tree *tree, char const *name, st_role const *role);


/**
 * @brief Add a constant declaration to protocol.
 *
 * @param[in,out] tree Sess type tree of protocol.
 * @param[in]     cons Constant struct.
 */
st_tree *st_tree_add_const(st_tree *tree, st_const_t con);


/**
 * @brief Add a role declaration to protocol.
 *
 * @param[in,out] tree Session type tree of protocol.
 * @param[in]     role Role to add.
 *
 * @returns Updated session types tree.
 */
st_tree *st_tree_add_role(st_tree *tree, st_role const *role);

/**
 * @brief Add a role group declaration to protocol.
 *
 * @param[in,out] tree Session type tree of protocol.
 * @param[in]     role Role group to add.
 *
 * @returns Updated session types tree.
 */
st_tree *st_tree_add_role_group(st_tree *tree, st_role_group const *group);


/**
 * @brief Add an import to protocol.
 *
 * @param[in,out] tree   Session type tree of protocol.
 * @param[in]     import Import details to add.
 *
 * @returns Updated session types tree.
 */
st_tree *st_tree_add_import(st_tree *tree, st_tree_import_t import);


/**
 * @brief Test if a string is a constant in the protocol.
 *
 * @param[in] tree Session type tree of protocol.
 * @param[in] name Constant name to test.
 *
 * @returns 1 if name is a defined constant, 0 otherwise.
 */
int st_tree_has_constant(st_tree *tree, char const *name);


/**
 * @brief Initialise session type node.
 *
 * @param[in,out] node Node to initialise.
 * @param[in]     type Type of node.
 *
 * @returns Initialised node.
 */
st_node *st_node_init(st_node *node, int type);


/**
 * @brief Append a node as a child to an existing node.
 *
 * @param[in,out] node  Parent node.
 * @param[in]     child Child node.
 *
 * @returns Updated parent node.
 */
st_node *st_node_append(st_node *node, st_node *child);


/**
 * @brief Resets the 'marked' flag on a st_node for debugging purposes.
 *
 * @param[in] node Node to reset flag.
 */
void st_node_reset_markedflag(st_node *node);


/**
 * @brief Compare two st_nodes recursively.
 * Errors will be marked on node->marked.
 *
 * @param[in,out] node  Node (scribble) to compare.
 * @param[in,out] other Node (source code) to compare.
 *
 * @returns 1 if identical, 0 otherwise.
 */
int st_node_compare_r(st_node *node, st_node *other);


/**
 * @brief Compare two message signature.
 *
 * @param[in] msgsig Message signature to compare.
 * @param[in] other  Message signature to compare.
 *
 * @returns 1 if identical, 0 otherwise.
 */
int st_node_compare_msgsig(const st_node_msgsig_t msgsig, const st_node_msgsig_t other);


/**
 * @brief Compare two st_nodes.
 *
 * @param[in] node  Node (scribble) to compare.
 * @param[in] other Node (source code) to compare.
 *
 * @returns 1 if identical, 0 otherwise.
 */
int st_node_compare(st_node *node, st_node *other);

int st_node_compare_interaction(st_node *node, st_node *other);

int st_node_is_overlapped(st_node *node, st_node *other);

#ifdef __cplusplus
}
#endif

#endif // SESSTYPE__ST_NODE__H__
