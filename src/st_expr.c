/**
 * \file
 * This file contains the tree representation of expressions
 * and provides functions to manipulate session type expressions.
 *
 * \headerfile "st_expr.h"
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "st_expr.h"

int st_expr_is_overlapped(const st_expr_t *e1, const st_expr_t *e2)
{
  int is_overlapped = 0;

  // This start from toplevel so the leave nodes could be in different format
  // but we will not get this far as long as the toplevel(s) are combinations of range and tuples
  //
  switch (e1->type) {
    case ST_EXPR_TYPE_RANGE:
      // Test whether the two ranges are not intersecting
      //
      // 1. If there is a variable, it can be overlapping (so always reject)
      // 2. If there is a constant, make sure
      // 2.1. e1 is before e2 (e1.max < e2.min)
      // 2.2. e2 is before e1 (e2.max < e1.min)
      //    Under the assumption that ranges are well-formed (min..max)
      //
      is_overlapped = (e1->binexpr->right->type == ST_EXPR_TYPE_CONST
                      && e2->binexpr->left->type == ST_EXPR_TYPE_CONST
                      && e1->binexpr->right->constant >= e2->binexpr->left->constant)
                    ||(e1->binexpr->left->type == ST_EXPR_TYPE_CONST
                      && e2->binexpr->right->type == ST_EXPR_TYPE_CONST
                      && e2->binexpr->right->constant >= e1->binexpr->left->constant);
      break;
    case ST_EXPR_TYPE_TUPLE:
      is_overlapped = st_expr_is_overlapped(e1->binexpr->left, e2->binexpr->left)
                    ||st_expr_is_overlapped(e1->binexpr->right, e2->binexpr->right);
      break;
    default:
      is_overlapped = 1; // Conservative heuristic
      break;
  }

  return is_overlapped;
}


int st_expr_is_identical(st_expr_t *expr, st_expr_t *other)
{
  int identical = 1;

  // If both of the expression are empty
  if (expr == NULL && other == NULL)
    return identical;

  // Otherwise compare the expression
  identical &= (expr->type == other->type);
  if (identical) {
    switch (expr->type) {
      case ST_EXPR_TYPE_CONST:
        identical &= (expr->constant == other->constant);
        break;

      case ST_EXPR_TYPE_VAR:
        identical &= (0 == strcmp(expr->variable, other->variable));
        break;

      // Binary operations
      case ST_EXPR_TYPE_RANGE:
      case ST_EXPR_TYPE_PLUS:
      case ST_EXPR_TYPE_MINUS:
      case ST_EXPR_TYPE_MULTIPLY:
      case ST_EXPR_TYPE_DIVIDE:
      case ST_EXPR_TYPE_MODULO:
      case ST_EXPR_TYPE_SHL:
      case ST_EXPR_TYPE_SHR:
      case ST_EXPR_TYPE_TUPLE:
      case ST_EXPR_TYPE_EQUAL:
      case ST_EXPR_TYPE_BIND:
      case ST_EXPR_TYPE_LT:
      case ST_EXPR_TYPE_LE:
        identical &= st_expr_is_identical(expr->binexpr->left, other->binexpr->left);
        identical &= st_expr_is_identical(expr->binexpr->right, other->binexpr->right);
        break;

      default:
        fprintf(stderr, "%s:%d %s Unknown expr type: %d\n", __FILE__, __LINE__, __FUNCTION__, expr->type);
        break;
    }
  }

  if (!identical) {
    fprintf(stderr, "Error: incompatible expression (%d and %d):\n", expr->type, other->type);
    st_expr_print(expr); printf(" and "); st_expr_print(other); printf("\n");
  }

  return identical;
}


st_expr_t *st_expr_copy(const st_expr_t *e)
{
  st_expr_t *dup_e;
  switch (e->type) {
    case ST_EXPR_TYPE_CONST:
      dup_e = st_expr_constant(e->constant);
      break;
    case ST_EXPR_TYPE_VAR:
      dup_e = st_expr_variable(e->variable);
      break;
    default:
      dup_e = st_expr_binexpr(st_expr_copy(e->binexpr->left), e->type, st_expr_copy(e->binexpr->right));
      break;
  }
  return dup_e;
}


st_expr_t *st_expr_offset_range(st_expr_t *range, st_expr_t* offset)
{
  assert(range->type == ST_EXPR_TYPE_RANGE || range->type == ST_EXPR_TYPE_TUPLE || range->type == ST_EXPR_TYPE_VAR || range->type == ST_EXPR_TYPE_CONST);

  // Offset = 0. No change.
  if (offset->type == ST_EXPR_TYPE_CONST && offset->constant == 0) return range;

  // Range is ST_EXPR_TYPE_RANGE. min + offset .. max + offset.
  if (range->type == ST_EXPR_TYPE_RANGE) {

    //
    // Range, this is the normal case.
    //
    range->binexpr->left = st_expr_binexpr(range->binexpr->left, ST_EXPR_TYPE_PLUS, offset);
    range->binexpr->right = st_expr_binexpr(range->binexpr->right, ST_EXPR_TYPE_PLUS, offset);

  } else if (range->type == ST_EXPR_TYPE_TUPLE && offset->type == ST_EXPR_TYPE_TUPLE) {

    //
    // Tuples, we run this separately for each component.
    //
    range->binexpr->left = st_expr_offset_range(range->binexpr->left, offset->binexpr->left);
    range->binexpr->right = st_expr_offset_range(range->binexpr->right, offset->binexpr->right);

  } else if (range->type == ST_EXPR_TYPE_VAR || range->type == ST_EXPR_TYPE_CONST) {

    range = st_expr_binexpr(range, ST_EXPR_TYPE_PLUS, offset);

  } else {

    fprintf(stderr, "%s: Invalid format of range and offset (Expecting RANGE + CONST/VAR offset or TUPLE + TUPLE offset)\n",
        __FUNCTION__);

  }

  st_expr_eval(range);
  return range;
}


inline st_expr_t *st_expr_constant(int val)
{
  st_expr_t *_ = (st_expr_t *)malloc(sizeof(st_expr_t));
  _->type = ST_EXPR_TYPE_CONST;
  _->constant = val;
  return _;
}


inline st_expr_t *st_expr_variable(const char *var)
{
  st_expr_t *_ = (st_expr_t *)malloc(sizeof(st_expr_t));
  _->type = ST_EXPR_TYPE_VAR;
  _->variable = strdup(var);
  return _;
}


inline st_expr_t *st_expr_binexpr(st_expr_t *left, int type, st_expr_t *right)
{
  st_expr_t *_ = (st_expr_t *)malloc(sizeof(st_expr_t));
  _->type = type;
  _->binexpr = (st_bin_expr_t *)malloc(sizeof(st_bin_expr_t));
  _->binexpr->left = left;
  _->binexpr->right = right;
  return _;
}
void st_expr_eval(st_expr_t *e)
{
  assert(e->type > 0);
  switch (e->type) {
    case ST_EXPR_TYPE_PLUS:
      st_expr_eval(e->binexpr->left);
      st_expr_eval(e->binexpr->right);

      if (ST_EXPR_TYPE_CONST == e->binexpr->left->type
          && ST_EXPR_TYPE_CONST == e->binexpr->right->type) {
        e->type = ST_EXPR_TYPE_CONST;
        int val = e->binexpr->left->constant + e->binexpr->right->constant;
        free(e->binexpr);
        e->constant = val;
      }

      if (ST_EXPR_TYPE_PLUS == e->type
          && ST_EXPR_TYPE_CONST == e->binexpr->right->type
          && e->binexpr->right->constant < 0) {
        e->type = ST_EXPR_TYPE_MINUS;
        e->binexpr->right->constant = -e->binexpr->right->constant;
      }

      // Simplifies the form: x + ? - y => ? + (x-y)
      if (ST_EXPR_TYPE_PLUS == e->type
          && ST_EXPR_TYPE_CONST == e->binexpr->left->type
          && ST_EXPR_TYPE_MINUS == e->binexpr->right->type
          && ST_EXPR_TYPE_VAR == e->binexpr->right->binexpr->left->type
          && ST_EXPR_TYPE_CONST == e->binexpr->right->binexpr->right->type) {
        int val = e->binexpr->left->constant - e->binexpr->right->binexpr->right->constant;
        if (val < 0) {
          free(e->binexpr->left); // constant
          st_expr_t *_tmp = e->binexpr->right;
          e->type = ST_EXPR_TYPE_MINUS;
          e->binexpr->left = e->binexpr->right->binexpr->left;
          e->binexpr->right = st_expr_constant(-val);
          //free(_tmp->binexpr->right); // constant
          //free(_tmp->binexpr);
        } else if (val == 0) {
          char *variable = strdup(e->binexpr->right->binexpr->left->variable);
          // TODO
          //free(e->binexpr->right->binexpr->left);
          //free(e->binexpr->right->binexpr->right);
          //free(e->binexpr->right->binexpr);
          //free(e->binexpr->right);
          //free(e->binexpr->left);
          //free(e->binexpr);
          e->type = ST_EXPR_TYPE_VAR;
          e->variable = variable;
        } else { // val > 0
          free(e->binexpr->left); // constant
          st_expr_t *_tmp = e->binexpr->right;
          e->type = ST_EXPR_TYPE_PLUS;
          e->binexpr->left = e->binexpr->right->binexpr->left;
          e->binexpr->right = st_expr_constant(val);
          //free(_tmp->binexpr->right); // constant
          //free(_tmp->binexpr);
        }
      }

      // Simplifies the form: ? - x + y=> ? + (x-y)
      if (ST_EXPR_TYPE_PLUS == e->type
          && ST_EXPR_TYPE_CONST == e->binexpr->right->type
          && ST_EXPR_TYPE_MINUS == e->binexpr->left->type
          && ST_EXPR_TYPE_VAR == e->binexpr->left->binexpr->left->type
          && ST_EXPR_TYPE_CONST == e->binexpr->left->binexpr->right->type) {
        int val = e->binexpr->right->constant - e->binexpr->left->binexpr->right->constant;
        if (val < 0) {
          //free(e->binexpr->left); // constant
          st_expr_t *_tmp = e->binexpr->right;
          e->type = ST_EXPR_TYPE_MINUS;
          e->binexpr->left = e->binexpr->left->binexpr->left;
          e->binexpr->right = st_expr_constant(-val);
          //free(_tmp->binexpr->right); // constant
          //free(_tmp->binexpr);
        } else if (val == 0) {
          char *variable = strdup(e->binexpr->left->binexpr->left->variable);
          //free(e->binexpr->right->binexpr->left);
          //free(e->binexpr->right->binexpr->right);
          //free(e->binexpr->right->binexpr);
          //free(e->binexpr->right);
          //free(e->binexpr->left);
          //free(e->binexpr);
          e->type = ST_EXPR_TYPE_VAR;
          e->variable = variable;
        } else { // val > 0
          //free(e->binexpr->left); // constant
          st_expr_t *_tmp = e->binexpr->right;
          e->type = ST_EXPR_TYPE_PLUS;
          e->binexpr->left = e->binexpr->left->binexpr->left;
          e->binexpr->right = st_expr_constant(val);
          //free(_tmp->binexpr->right); // constant
          //free(_tmp->binexpr);
        }
        st_expr_eval(e);
      }

      // X + (y - X)
      if (ST_EXPR_TYPE_PLUS == e->type
          && ST_EXPR_TYPE_VAR == e->binexpr->left->type
          && ST_EXPR_TYPE_MINUS == e->binexpr->right->type
          && ST_EXPR_TYPE_CONST == e->binexpr->right->binexpr->left->type
          && ST_EXPR_TYPE_VAR == e->binexpr->right->binexpr->right->type
          && 0 == strcmp(e->binexpr->left->variable, e->binexpr->right->binexpr->right->variable)) {
        int val = e->binexpr->right->binexpr->left->constant;
        //free(e->binexpr->right->binexpr->left);
        //free(e->binexpr->right->binexpr->right);
        //free(e->binexpr->right->binexpr);
        //free(e->binexpr->right);
        //free(e->binexpr->left);
        //free(e->binexpr);
        e->type = ST_EXPR_TYPE_CONST;
        e->constant = val;
      }

      // (0 - x) + y ==> y - x
      if (ST_EXPR_TYPE_PLUS == e->type
          && ST_EXPR_TYPE_CONST == e->binexpr->right->type
          && ST_EXPR_TYPE_MINUS == e->binexpr->left->type
          && ST_EXPR_TYPE_CONST == e->binexpr->left->binexpr->left->type
          && 0 == e->binexpr->left->binexpr->left->constant) {
        e->type = ST_EXPR_TYPE_MINUS;
        st_expr_t *_tmp = e->binexpr->left;
        e->binexpr->left = e->binexpr->right;
        e->binexpr->right = _tmp->binexpr->right;
        free(_tmp->binexpr->left);

        st_expr_eval(e);
      }
      break;

    case ST_EXPR_TYPE_MINUS:
      st_expr_eval(e->binexpr->left);
      st_expr_eval(e->binexpr->right);
      if (ST_EXPR_TYPE_CONST == e->binexpr->left->type
          && ST_EXPR_TYPE_CONST == e->binexpr->right->type) {
        e->type = ST_EXPR_TYPE_CONST;
        int val = e->binexpr->left->constant - e->binexpr->right->constant;
        free(e->binexpr);
        e->constant = val;
      }
      break;

    case ST_EXPR_TYPE_MULTIPLY:
      st_expr_eval(e->binexpr->left);
      st_expr_eval(e->binexpr->right);
      if (ST_EXPR_TYPE_CONST == e->binexpr->left->type
          && ST_EXPR_TYPE_CONST == e->binexpr->right->type) {
        e->type = ST_EXPR_TYPE_CONST;
        int val = e->binexpr->left->constant * e->binexpr->right->constant;
        free(e->binexpr);
        e->constant = val;
      }
      break;

    case ST_EXPR_TYPE_MODULO:
      st_expr_eval(e->binexpr->left);
      st_expr_eval(e->binexpr->right);
      if (ST_EXPR_TYPE_CONST == e->binexpr->left->type
          && ST_EXPR_TYPE_CONST == e->binexpr->right->type) {
        e->type = ST_EXPR_TYPE_CONST;
        int val = e->binexpr->left->constant % e->binexpr->right->constant;
        free(e->binexpr);
        e->constant = val;
      }
      break;

    case ST_EXPR_TYPE_DIVIDE:
      st_expr_eval(e->binexpr->left);
      st_expr_eval(e->binexpr->right);
      if (ST_EXPR_TYPE_CONST == e->binexpr->left->type
          && ST_EXPR_TYPE_CONST == e->binexpr->right->type) {
        e->type = ST_EXPR_TYPE_CONST;
        int val = e->binexpr->left->constant / e->binexpr->right->constant;
        free(e->binexpr);
        e->constant = val;
      }
      break;

    case ST_EXPR_TYPE_SHL:
      st_expr_eval(e->binexpr->left);
      st_expr_eval(e->binexpr->right);
      if (ST_EXPR_TYPE_CONST == e->binexpr->left->type
          && ST_EXPR_TYPE_CONST == e->binexpr->right->type) {
        e->type = ST_EXPR_TYPE_CONST;
        int val = e->binexpr->left->constant << e->binexpr->right->constant;
        free(e->binexpr);
        e->constant = val;
      }
      break;

    case ST_EXPR_TYPE_SHR:
      st_expr_eval(e->binexpr->left);
      st_expr_eval(e->binexpr->right);
      if (ST_EXPR_TYPE_CONST == e->binexpr->left->type
          && ST_EXPR_TYPE_CONST == e->binexpr->right->type) {
        e->type = ST_EXPR_TYPE_CONST;
        int val = e->binexpr->left->constant >> e->binexpr->right->constant;
        free(e->binexpr);
        e->constant = val;
      }
      break;

    case ST_EXPR_TYPE_RANGE:
      st_expr_eval(e->binexpr->left);
      st_expr_eval(e->binexpr->right);

      if (ST_EXPR_TYPE_VAR == e->binexpr->left->type
          && ST_EXPR_TYPE_VAR == e->binexpr->right->type
          && 0 == strcmp(e->binexpr->left->variable, e->binexpr->right->variable)) {
        char *var = strdup(e->binexpr->left->variable);
        //free(e->binexpr->left);
        //free(e->binexpr->right);
        //free(e->binexpr);
        e->type = ST_EXPR_TYPE_VAR;
        e->variable = var;
      }

      if (ST_EXPR_TYPE_RANGE == e->type
          && ST_EXPR_TYPE_CONST == e->binexpr->left->type
          && ST_EXPR_TYPE_CONST == e->binexpr->right->type
          && e->binexpr->left->constant == e->binexpr->right->constant) {
        int val = e->binexpr->right->constant+0;
        //free(e->binexpr->left);
        //free(e->binexpr->right);
        //free(e->binexpr);
        e->type = ST_EXPR_TYPE_CONST;
        e->constant = val;
      }
      break;
  }
}

void st_expr_subst_var(st_expr_t *e, const char *name, int value)
{
  assert(e->type > 0);
  if (e->type == ST_EXPR_TYPE_CONST) return;

  if (e->type == ST_EXPR_TYPE_VAR) {
    if (0 == strcmp(name, e->variable)) {
      e->type = ST_EXPR_TYPE_CONST;
      e->constant = value;
    }
    return;
  }

  st_expr_subst_var(e->binexpr->left, name, value);
  st_expr_subst_var(e->binexpr->right, name, value);
}

void st_expr_print(st_expr_t *e)
{
  assert(e->type > 0);
  st_expr_eval(e);
  switch (e->type) {
    case ST_EXPR_TYPE_RANGE:
      st_expr_print(e->binexpr->left);
      printf("..");
      st_expr_print(e->binexpr->right);
      break;
    case ST_EXPR_TYPE_PLUS:
      printf("(");
      st_expr_print(e->binexpr->left);
      printf("+");
      st_expr_print(e->binexpr->right);
      printf(")");
      break;
    case ST_EXPR_TYPE_MINUS:
      printf("(");
      st_expr_print(e->binexpr->left);
      printf("-");
      st_expr_print(e->binexpr->right);
      printf(")");
      break;
    case ST_EXPR_TYPE_MULTIPLY:
      printf("(");
      st_expr_print(e->binexpr->left);
      printf("*");
      st_expr_print(e->binexpr->right);
      printf(")");
      break;
    case ST_EXPR_TYPE_MODULO:
      printf("(");
      st_expr_print(e->binexpr->left);
      printf("%%");
      st_expr_print(e->binexpr->right);
      printf(")");
      break;
    case ST_EXPR_TYPE_DIVIDE:
      printf("(");
      st_expr_print(e->binexpr->left);
      printf("/");
      st_expr_print(e->binexpr->right);
      printf(")");
      break;
    case ST_EXPR_TYPE_SHL:
      printf("(");
      st_expr_print(e->binexpr->left);
      printf("<<");
      st_expr_print(e->binexpr->right);
      printf(")");
      break;
    case ST_EXPR_TYPE_SHR:
      printf("(");
      st_expr_print(e->binexpr->left);
      printf(">>");
      st_expr_print(e->binexpr->right);
      printf(")");
      break;
    case ST_EXPR_TYPE_TUPLE:
      st_expr_print(e->binexpr->left);
      printf("][");
      st_expr_print(e->binexpr->right);
      break;
    case ST_EXPR_TYPE_EQUAL:
      st_expr_print(e->binexpr->left);
      printf("==");
      st_expr_print(e->binexpr->right);
      break;
    case ST_EXPR_TYPE_BIND:
      st_expr_print(e->binexpr->left);
      printf(":");
      st_expr_print(e->binexpr->right);
      break;
    case ST_EXPR_TYPE_CONST:
      printf("%d", e->constant);
      break;
    case ST_EXPR_TYPE_VAR:
      printf("%s", e->variable);
      break;
    default:
      fprintf(stderr, "%s:%d %s Unknown expr type: %d\n", __FILE__, __LINE__, __FUNCTION__, e->type);
  }
}
