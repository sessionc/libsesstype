#ifndef SESSTYPE__ST_EXPR__H__
#define SESSTYPE__ST_EXPR__H__
/**
 * \file
 * This file contains the tree representation of expressions
 * and provides functions to manipulate session type expressions.
 *
 */

#ifdef __cplusplus
extern "C" {
#endif


#define ST_EXPR_TYPE_CONST 1 // Constant
#define ST_EXPR_TYPE_VAR   2 // Variable

#define ST_EXPR_TYPE_ADD 3 // +
#define ST_EXPR_TYPE_SUB 4 // -
#define ST_EXPR_TYPE_MUL 5 // *
#define ST_EXPR_TYPE_DIV 6 // /
#define ST_EXPR_TYPE_MOD 7 // &
#define ST_EXPR_TYPE_SHL 8 // <<
#define ST_EXPR_TYPE_SHR 9 // >>

#define ST_EXPR_TYPE_SEQ 10 // , (Sequence)
#define ST_EXPR_TYPE_RNG 11 // .. (Range)


struct __st_bin_expr_t {
  struct __st_expr_t *left;
  struct __st_expr_t *right;
};

struct __st_seq_expr_t {
  unsigned int count;
  int *values;
};

struct __st_rng_expr_t {
  char *bindvar;
  struct __st_expr_t *from;
  struct __st_expr_t *to;
};

struct __st_expr_t {
  int type;
  union {
    struct __st_bin_expr_t *bin;
    struct __st_seq_expr_t *seq;
    struct __st_rng_expr_t *rng;
    char *var;
    int num;
  };
};

typedef struct __st_expr_t     st_expr;       /**< Generic expression. */

typedef struct __st_bin_expr_t st_bin_expr_t; /**< Binary expression. */
typedef struct __st_seq_expr_t st_seq_expr_t; /**< Sequence [int] expression. */
typedef struct __st_rng_expr_t st_rng_expr_t; /**< Range expression. */

/**
 * Expression list.
 */
typedef struct {
  int count;
  st_expr **exprs;
} st_expr_list;


/**
 * \brief Helper constructor for binary expression.
 *
 * @param[in] left  LHS expression tree.
 * @param[in] type  Expression type as defined in st_node.h (ST_EXPR_TYPE_*)
 * @param[in] right RHS expression tree.
 *
 * \returns expression with binary expression (dynamically allocated).
 */
st_expr *st_expr_binary(st_expr *left, int type, st_expr *right);


/**
 * \brief Helper constructor for 'constant' expression.
 *
 * @param[in] num Integer value.
 *
 * \returns expression with constant value (dynamically allocated).
 */
st_expr *st_expr_constant(int num);

/**
 * \brief Test if two expressions are identical.
 *
 * @param[in] e0 Expression to compare.
 * @param[in] e1 Expression to compare.
 *
 * \returns 1 if identical, 0 otherwise.
 */
int st_expr_is_identical(st_expr *e0, st_expr *e1);


/**
 * \brief Print an expression to stdout.
 *
 * @param[in] expr Expression to print.
 */
void st_expr_print(st_expr *e);


/**
 * \brief Helper constructor for range expression.
 *
 * @param[in] from LHS from expression.
 * @param[in] to   RHS to expression.
 *
 * \returns Range exprssion.
 */
st_expr *st_expr_range(st_expr *from, st_expr *to);


/**
 * \brief Helper constructor for range expression.
 *
 * @param[in] bindvar Bind variable.
 * @param[in] from    LHS from expression.
 * @param[in] to      RHS to expression.
 *
 * \returns Range exprssion.
 */
st_rng_expr_t *st_expr_init_rng(char *bindvar, st_expr *from, st_expr *to);


/**
 * \brief Print an expression to a string.
 *
 * @param[out] str  Output string.
 * @param[in]  expr Expression to print.
 */
void st_expr_sprint(char *str, st_expr *e);


/**
 * \brief Print an expression to a given output stream.
 *
 * @param[out] stream Output stream.
 * @param[in]  expr   Expression to print.
 */
void st_expr_fprint(FILE *stream, st_expr *e);


/**
 * \brief Pretty print an expression.
 *
 * @param[in] e   Expression to print.
 */
void st_expr_print(st_expr *e);


/**
 * \brief Evaluate an expression.
 *
 * Simplify mathematical expressions
 * and return a canonical form if possible.
 *
 * @param[in,out] e Expression to evaluate.
 */
void st_expr_eval(st_expr *e);


/**
 * \brief Helper constructor for 'variable' expression.
 *
 * @param[in] var Variable name.
 *
 * \returns expression with variable (dynamically allocated).
 */
st_expr *st_expr_variable(const char *var);


/**
 * \brief Deep copy an expression.
 *
 * @param[in] e Expression to copy.
 *
 * \returns pointer to dynamically allocated copy of expression.
 */
st_expr *st_expr_copy(const st_expr *e);


/**
 * \brief Free an exprssion.
 *
 * @param[in] e Expression to free.
 */
void st_expr_free(st_expr *e);


/**
 * \brief Apply a relative expression on a binding range.
 *
 * @param[in] b Binding range.
 * @param[in] e Relative expression.
 *
 * \returns pointer to dynamically allocated expression.
 */
st_expr *st_expr_apply(const st_expr *b, const st_expr *e);


/**
 * \brief Invert an expression.
 *
 * Currently only work with + - * / expressions
 * and with numeric value on RHS.
 *
 * @param[in] e Expression to invert.
 *
 * \returns an inverted expression or NULL if not possible.
 */
st_expr *st_expr_inv(const st_expr *e);


#ifdef __cplusplus
}
#endif

#endif // SESSTYPE__ST_EXPR__H__
