#ifndef ST_EXPR__H__
#define ST_EXPR__H__
/**
 * \file
 * This file contains the tree representation of expressions
 * and provides functions to manipulate session type expressions.
 *
 */

#ifdef __cplusplus
extern "C" {
#endif


#define ST_EXPR_TYPE_CONST 1
#define ST_EXPR_TYPE_VAR   2
#define ST_EXPR_TYPE_RANGE 3
#define ST_EXPR_TYPE_PLUS  4
#define ST_EXPR_TYPE_MINUS 5
#define ST_EXPR_TYPE_MULTIPLY 6
#define ST_EXPR_TYPE_DIVIDE 7
#define ST_EXPR_TYPE_MODULO 8
#define ST_EXPR_TYPE_SHL 9
#define ST_EXPR_TYPE_SHR 10
#define ST_EXPR_TYPE_TUPLE 11
#define ST_EXPR_TYPE_EQUAL 12
#define ST_EXPR_TYPE_BIND 13
#define ST_EXPR_TYPE_LT 14
#define ST_EXPR_TYPE_LE 15


// Binary expressions
struct __st_bin_expr_t {
  struct __st_expr_t *left;
  struct __st_expr_t *right;
};


struct __st_expr_t {
  int type;
  union {
    struct __st_bin_expr_t *binexpr;
    int constant;
    char *variable;
  };
};


typedef struct __st_bin_expr_t st_bin_expr_t;
typedef struct __st_expr_t st_expr_t;


/**
 * \brief Helper constructor for binary expression.
 *
 * @param[in] left  LHS expression tree.
 * @param[in] type  Expression type as defined in st_node.h (ST_EXPR_TYPE_*)
 * @param[in] right RHS expression tree.
 *
 * \returns expression with binary expression (dynamically allocated).
 */
st_expr_t *st_expr_binexpr(st_expr_t *left, int type, st_expr_t *right);


/**
 * \brief Helper constructor for 'constant' expression.
 *
 * @param[in] val Integer value.
 *
 * \returns expression with constant value (dynamically allocated).
 */
st_expr_t *st_expr_constant(int val);


/**
 * \brief Helper constructor for 'variable' expression.
 *
 * @param[in] var Variable name.
 *
 * \returns expression with variable (dynamically allocated).
 */
st_expr_t *st_expr_variable(const char *var);


/**
 * \brief Compare two expressions.
 *
 * @param[in] e1 Expression to compare.
 * @param[in] e2 Expression to compare.
 *
 * \returns 1 if identical, 0 otherwise.
 *
 */
int st_expr_is_identical(st_expr_t *e1, st_expr_t *e2);


/**
 * \brief Get a copy of an expression.
 * 
 * @param[in] expr Expression to copy.
 *
 * \returns a copy of expr.
 */
st_expr_t *st_expr_copy(const st_expr_t *expr);

/**
 * \brief Helper function to simplofy a range expression
 *        in the form of X..X to X.
 *
 * If toplevel expression is not range or not in X..X format
 * original expression will be returned.
 *
 * @param[in] e Expression to simplify.
 *
 * \returns simplified expression.
 */
st_expr_t *st_expr_simplify(st_expr_t *e);


/**
 * \brief Evaluate an expression.
 *
 * Simplify mathematical expressions
 * and return a canonical form if possible.
 *
 * @param[in,out] e Expression to evaluate.
 */
void st_expr_eval(st_expr_t *e);


/**
 * \brief Calculate the resulting expression given
 *        a range and an offset.
 *
 * @param[in] range  Expression range.
 * @param[in] offset Expression offset (for both start and end).
 *
 * \returns resulting expression.
 */
st_expr_t *st_expr_offset_range(st_expr_t *range, st_expr_t* offset);


/**
 * \brief Checks if two expressions are overlapped
 *        (identical or common range).
 *
 * @param[in] e1 Expression to compare.
 * @param[in] e2 Expression to compare.
 *
 * \returns 1 if overlapped, 0 otherwise.
 */
int st_expr_is_overlapped(const st_expr_t *e1, const st_expr_t *e2);


/**
 * \brief Print an expression to stdout.
 *
 * @param[in] expr Expression to print
 */
void st_expr_print(st_expr_t *e);


#ifdef __cplusplus
}
#endif

#endif // ST_EXPR__H__
