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

#include "sesstype/st_expr.h"


inline st_expr *st_expr_constant(int num)
{
  st_expr *_ = (st_expr *)malloc(sizeof(st_expr));
  _->type = ST_EXPR_TYPE_CONST;
  _->num = num;
  return _;
}


inline st_expr *st_expr_variable(const char *var)
{
  st_expr *_ = (st_expr *)malloc(sizeof(st_expr));
  _->type = ST_EXPR_TYPE_VAR;
  _->var = strdup(var);
  return _;
}


inline st_expr *st_expr_binary(st_expr *left, int type, st_expr *right)
{
  st_expr *_ = (st_expr *)malloc(sizeof(st_expr));
  _->type = type;
  _->bin = (st_bin_expr_t *)malloc(sizeof(st_bin_expr_t));
  _->bin->left = left;
  _->bin->right = right;
  return _;
}


inline st_expr *st_expr_range(st_expr *from, st_expr *to)
{
  st_expr *_ = (st_expr *)malloc(sizeof(st_expr));
  _->type = ST_EXPR_TYPE_RNG;
  _->rng = st_expr_init_rng("_", from, to);
  return _;
}

inline st_rng_expr_t *st_expr_init_rng(char *bindvar, st_expr *from, st_expr *to)
{
  st_rng_expr_t *_ = (st_rng_expr_t *)malloc(sizeof(st_rng_expr_t));
  _->bindvar = bindvar;
  _->from = from;
  _->to = to;
  return _;
}


void st_expr_eval(st_expr *e)
{
  assert(e->type > 0);
  switch (e->type) {
    case ST_EXPR_TYPE_ADD:
      st_expr_eval(e->bin->left);
      st_expr_eval(e->bin->right);

      if (ST_EXPR_TYPE_CONST == e->bin->left->type
          && ST_EXPR_TYPE_CONST == e->bin->right->type) {
        e->type = ST_EXPR_TYPE_CONST;
        int val = e->bin->left->num + e->bin->right->num;
        free(e->bin);
        e->num = val;
      }

      if (ST_EXPR_TYPE_ADD == e->type
          && ST_EXPR_TYPE_CONST == e->bin->right->type
          && e->bin->right->num < 0) {
        e->type = ST_EXPR_TYPE_SUB;
        e->bin->right->num = -e->bin->right->num;
      }

      // Simplifies the form: x + ? - y => ? + (x-y)
      if (ST_EXPR_TYPE_ADD == e->type
          && ST_EXPR_TYPE_CONST == e->bin->left->type
          && ST_EXPR_TYPE_SUB == e->bin->right->type
          && ST_EXPR_TYPE_VAR == e->bin->right->bin->left->type
          && ST_EXPR_TYPE_CONST == e->bin->right->bin->right->type) {
        int val = e->bin->left->num - e->bin->right->bin->right->num;
        if (val < 0) {
          free(e->bin->left); // value
          e->type = ST_EXPR_TYPE_SUB;
          e->bin->left = e->bin->right->bin->left;
          e->bin->right = st_expr_constant(-val);
        } else if (val == 0) {
          char *variable = strdup(e->bin->right->bin->left->var);
          e->type = ST_EXPR_TYPE_VAR;
          e->var = variable;
        } else { // val > 0
          free(e->bin->left); // value
          e->type = ST_EXPR_TYPE_ADD;
          e->bin->left = e->bin->right->bin->left;
          e->bin->right = st_expr_constant(val);
        }
      }

      // Simplifies the form: ? - x + y=> ? + (x-y)
      if (ST_EXPR_TYPE_ADD == e->type
          && ST_EXPR_TYPE_CONST == e->bin->right->type
          && ST_EXPR_TYPE_SUB == e->bin->left->type
          && ST_EXPR_TYPE_VAR == e->bin->left->bin->left->type
          && ST_EXPR_TYPE_CONST == e->bin->left->bin->right->type) {
        int val = e->bin->right->num - e->bin->left->bin->right->num;
        if (val < 0) {
          e->type = ST_EXPR_TYPE_SUB;
          e->bin->left = e->bin->left->bin->left;
          e->bin->right = st_expr_constant(-val);
        } else if (val == 0) {
          char *variable = strdup(e->bin->left->bin->left->var);
          e->type = ST_EXPR_TYPE_VAR;
          e->var = variable;
        } else { // val > 0
          e->type = ST_EXPR_TYPE_ADD;
          e->bin->left = e->bin->left->bin->left;
          e->bin->right = st_expr_constant(val);
        }
        st_expr_eval(e);
      }

      // X + (y - X)
      if (ST_EXPR_TYPE_ADD == e->type
          && ST_EXPR_TYPE_VAR == e->bin->left->type
          && ST_EXPR_TYPE_SUB == e->bin->right->type
          && ST_EXPR_TYPE_CONST == e->bin->right->bin->left->type
          && ST_EXPR_TYPE_VAR == e->bin->right->bin->right->type
          && 0 == strcmp(e->bin->left->var, e->bin->right->bin->right->var)) {
        int val = e->bin->right->bin->left->num;
        e->type = ST_EXPR_TYPE_CONST;
        e->num = val;
      }

      // (0 - x) + y ==> y - x
      if (ST_EXPR_TYPE_ADD == e->type
          && ST_EXPR_TYPE_CONST == e->bin->right->type
          && ST_EXPR_TYPE_SUB == e->bin->left->type
          && ST_EXPR_TYPE_CONST == e->bin->left->bin->left->type
          && 0 == e->bin->left->bin->left->num) {
        e->type = ST_EXPR_TYPE_SUB;
        st_expr *_tmp = e->bin->left;
        e->bin->left = e->bin->right;
        e->bin->right = _tmp->bin->right;
        free(_tmp->bin->left);

        st_expr_eval(e);
      }
      break;

    case ST_EXPR_TYPE_SUB:
      st_expr_eval(e->bin->left);
      st_expr_eval(e->bin->right);
      if (ST_EXPR_TYPE_CONST == e->bin->left->type
          && ST_EXPR_TYPE_CONST == e->bin->right->type) {
        e->type = ST_EXPR_TYPE_CONST;
        int val = e->bin->left->num - e->bin->right->num;
        free(e->bin);
        e->num = val;
      }
      break;

    case ST_EXPR_TYPE_MUL:
      st_expr_eval(e->bin->left);
      st_expr_eval(e->bin->right);
      if (ST_EXPR_TYPE_CONST == e->bin->left->type
          && ST_EXPR_TYPE_CONST == e->bin->right->type) {
        e->type = ST_EXPR_TYPE_CONST;
        int val = e->bin->left->num * e->bin->right->num;
        free(e->bin);
        e->num = val;
      }
      break;

    case ST_EXPR_TYPE_MOD:
      st_expr_eval(e->bin->left);
      st_expr_eval(e->bin->right);
      if (ST_EXPR_TYPE_CONST == e->bin->left->type
          && ST_EXPR_TYPE_CONST == e->bin->right->type) {
        e->type = ST_EXPR_TYPE_CONST;
        int val = e->bin->left->num % e->bin->right->num;
        free(e->bin);
        e->num = val;
      }
      break;

    case ST_EXPR_TYPE_DIV:
      st_expr_eval(e->bin->left);
      st_expr_eval(e->bin->right);
      if (ST_EXPR_TYPE_CONST == e->bin->left->type
          && ST_EXPR_TYPE_CONST == e->bin->right->type) {
        e->type = ST_EXPR_TYPE_CONST;
        int val = e->bin->left->num / e->bin->right->num;
        free(e->bin);
        e->num = val;
      }
      break;

    case ST_EXPR_TYPE_SHL:
      st_expr_eval(e->bin->left);
      st_expr_eval(e->bin->right);
      if (ST_EXPR_TYPE_CONST == e->bin->left->type
          && ST_EXPR_TYPE_CONST == e->bin->right->type) {
        e->type = ST_EXPR_TYPE_CONST;
        int val = e->bin->left->num << e->bin->right->num;
        free(e->bin);
        e->num = val;
      }
      break;

    case ST_EXPR_TYPE_SHR:
      st_expr_eval(e->bin->left);
      st_expr_eval(e->bin->right);
      if (ST_EXPR_TYPE_CONST == e->bin->left->type
          && ST_EXPR_TYPE_CONST == e->bin->right->type) {
        e->type = ST_EXPR_TYPE_CONST;
        int val = e->bin->left->num >> e->bin->right->num;
        free(e->bin);
        e->num = val;
      }
      break;

    case ST_EXPR_TYPE_RNG:
      st_expr_eval(e->rng->from);
      st_expr_eval(e->rng->to);

      /*
      if (ST_EXPR_TYPE_VAR == e->rng->from->type
          && ST_EXPR_TYPE_VAR == e->rng->to->type
          && 0 == strcmp(e->rng->from->var, e->rng->to->var)) {
        char *var = strdup(e->rng->from->var);
        e->type = ST_EXPR_TYPE_VAR;
        e->var = var;
      }*/

      if (ST_EXPR_TYPE_RNG == e->type
          && ST_EXPR_TYPE_CONST == e->rng->from->type
          && ST_EXPR_TYPE_CONST == e->rng->to->type
          && e->rng->from->num == e->rng->to->num) {
        int val = e->rng->to->num+0;
        e->type = ST_EXPR_TYPE_CONST;
        e->num = val;
      }
      break;
  }
}

void st_expr_free(st_expr *e)
{
  assert(e->type > 0);
  switch (e->type) {
    case ST_EXPR_TYPE_VAR:
      free(e->var);
      free(e);
      break;
    case ST_EXPR_TYPE_CONST:
      free(e);
      break;
    case ST_EXPR_TYPE_ADD:
    case ST_EXPR_TYPE_SUB:
    case ST_EXPR_TYPE_MUL:
    case ST_EXPR_TYPE_DIV:
    case ST_EXPR_TYPE_MOD:
    case ST_EXPR_TYPE_SHL:
    case ST_EXPR_TYPE_SHR:
      st_expr_free(e->bin->left);
      st_expr_free(e->bin->right);
      free(e->bin);
      free(e);
      break;
    case ST_EXPR_TYPE_SEQ:
      free(e->seq->values);
      e->seq->count = 0;
      free(e->seq);
      free(e);
      break;
    case ST_EXPR_TYPE_RNG:
      free(e->rng->bindvar);
      st_expr_free(e->rng->from);
      st_expr_free(e->rng->to);
      free(e->rng);
      free(e);
      break;
    default:
      fprintf(stderr, "%s:%d %s Unknown expr type: %d\n", __FILE__, __LINE__, __FUNCTION__, e->type);
  }
}


void st_expr_fprint(FILE *stream, st_expr *e)
{
  assert(e->type > 0);
  st_expr_eval(e);
  switch (e->type) {
    case ST_EXPR_TYPE_CONST:
      fprintf(stream, "%d", e->num);
      break;
    case ST_EXPR_TYPE_VAR:
      fprintf(stream, "%s", e->var);
      break;
    case ST_EXPR_TYPE_ADD:
      fprintf(stream, "(");
      st_expr_fprint(stream, e->bin->left);
      fprintf(stream, "+");
      st_expr_fprint(stream, e->bin->right);
      fprintf(stream, ")");
      break;
    case ST_EXPR_TYPE_SUB:
      fprintf(stream, "(");
      st_expr_fprint(stream, e->bin->left);
      fprintf(stream, "-");
      st_expr_fprint(stream, e->bin->right);
      fprintf(stream, ")");
      break;
    case ST_EXPR_TYPE_MUL:
      fprintf(stream, "(");
      st_expr_fprint(stream, e->bin->left);
      fprintf(stream, "*");
      st_expr_fprint(stream, e->bin->right);
      fprintf(stream, ")");
      break;
    case ST_EXPR_TYPE_DIV:
      fprintf(stream, "(");
      st_expr_fprint(stream, e->bin->left);
      fprintf(stream, "/");
      st_expr_fprint(stream, e->bin->right);
      fprintf(stream, ")");
      break;
    case ST_EXPR_TYPE_MOD:
      fprintf(stream, "(");
      st_expr_fprint(stream, e->bin->left);
      fprintf(stream, "%%");
      st_expr_fprint(stream, e->bin->right);
      fprintf(stream, ")");
      break;
    case ST_EXPR_TYPE_SHL:
      fprintf(stream, "(");
      st_expr_fprint(stream, e->bin->left);
      fprintf(stream, "<<");
      st_expr_fprint(stream, e->bin->right);
      fprintf(stream, ")");
      break;
    case ST_EXPR_TYPE_SHR:
      fprintf(stream, "(");
      st_expr_fprint(stream, e->bin->left);
      fprintf(stream, ">>");
      st_expr_fprint(stream, e->bin->right);
      fprintf(stream, ")");
      break;
    case ST_EXPR_TYPE_SEQ:
      if (e->seq->count > 0) {
        fprintf(stream, "%d", e->seq->values[0]);
      }
      for (int i=1; i<e->seq->count; i++) {
        fprintf(stream, ",%d", e->seq->values[i]);
      }
      break;
    case ST_EXPR_TYPE_RNG:
      if (e->rng->bindvar != NULL && strlen(e->rng->bindvar) > 0 && 0 != strcmp(e->rng->bindvar, "_")) {
        fprintf(stream, "%s:", e->rng->bindvar);
      }
      st_expr_fprint(stream, e->rng->from);
      fprintf(stream, "..");
      st_expr_fprint(stream, e->rng->to);
      break;
    default:
      fprintf(stderr, "%s:%d %s Unknown expr type: %d\n", __FILE__, __LINE__, __FUNCTION__, e->type);
  }

}

inline void st_expr_print(st_expr *e)
{
  st_expr_fprint(stdout, e);
}

int st_expr_is_identical(st_expr *e0, st_expr *e1)
{
  assert(0/*TODO*/);
  return 0;
}


st_expr *st_expr_copy(const st_expr *e)
{
  st_expr *newe = (st_expr *)malloc(sizeof(st_expr));
  memcpy(newe, e, sizeof(st_expr));
  newe->type = e->type;
  switch (e->type) {
    case ST_EXPR_TYPE_ADD:
    case ST_EXPR_TYPE_SUB:
    case ST_EXPR_TYPE_MUL:
    case ST_EXPR_TYPE_DIV:
    case ST_EXPR_TYPE_MOD:
    case ST_EXPR_TYPE_SHL:
    case ST_EXPR_TYPE_SHR:
      newe->bin = (st_bin_expr_t *)malloc(sizeof(st_bin_expr_t));
      newe->bin->left = st_expr_copy(e->bin->left);
      newe->bin->right = st_expr_copy(e->bin->right);
      break;

    case ST_EXPR_TYPE_SEQ:
      newe->seq = (st_seq_expr_t *)malloc(sizeof(st_seq_expr_t));
      newe->seq->count = e->seq->count;
      newe->seq->values = (int *)calloc(newe->seq->count, sizeof(int));
      memcpy(newe->seq->values, e->seq->values, newe->seq->count * sizeof(int));
      break;

    case ST_EXPR_TYPE_RNG:
      newe->rng = (st_rng_expr_t *)malloc(sizeof(st_rng_expr_t));
      newe->rng->bindvar = strdup(e->rng->bindvar);
      newe->rng->from = st_expr_copy(e->rng->from);
      newe->rng->to = st_expr_copy(e->rng->to);
      break;

    case ST_EXPR_TYPE_CONST:
      newe->num = e->num;
      break;

    case ST_EXPR_TYPE_VAR:
      newe->var = strdup(e->var);
      break;

    default:
      fprintf(stderr, "%s:%d %s Unknown expr type: %d\n", __FILE__, __LINE__, __FUNCTION__, e->type);
  }
  return newe;
}

st_expr *st_expr_replace(const st_expr *in, const char *var, const st_expr *by)
{
  st_expr *newe = (st_expr *)malloc(sizeof(st_expr));
  switch (in->type) {
    case ST_EXPR_TYPE_ADD:
    case ST_EXPR_TYPE_SUB:
    case ST_EXPR_TYPE_MUL:
    case ST_EXPR_TYPE_DIV:
    case ST_EXPR_TYPE_MOD:
    case ST_EXPR_TYPE_SHL:
    case ST_EXPR_TYPE_SHR:
      newe->type = in->type;
      newe->bin = (st_bin_expr_t *)malloc(sizeof(st_bin_expr_t));
      newe->bin->left = st_expr_replace(in->bin->left, var, by);
      newe->bin->right = st_expr_replace(in->bin->right, var, by);
      return newe;

    case ST_EXPR_TYPE_SEQ:
      newe->type = in->type;
      newe->seq = (st_seq_expr_t *)malloc(sizeof(st_seq_expr_t));
      newe->seq->count = in->seq->count;
      newe->seq->values = (int *)calloc(newe->seq->count, sizeof(int));
      memcpy(newe->seq->values, in->seq->values, sizeof(int)*newe->seq->count);
      return newe;

    case ST_EXPR_TYPE_RNG:
      newe->type = in->type;
      newe->rng = (st_rng_expr_t *)malloc(sizeof(st_rng_expr_t));
      newe->rng->bindvar = strdup(in->rng->bindvar);
      newe->rng->from = st_expr_replace(in->rng->from, var, by);
      newe->rng->to = st_expr_replace(in->rng->to, var, by);
      return newe;

    case ST_EXPR_TYPE_CONST:
      newe->type = in->type;
      newe->num = in->num;
      return newe;

    case ST_EXPR_TYPE_VAR:
      if (strcmp(in->var, var) == 0) {
        free(newe);
        return st_expr_copy(by);
      }
      newe->type = in->type;
      newe->var = strdup(in->var);
      return newe;

    default:
      fprintf(stderr, "%s:%d %s Unknown expr type: %d\n", __FILE__, __LINE__, __FUNCTION__, in->type);
      return NULL;
  }
}


st_expr *st_expr_apply(const st_expr *b, const st_expr *e)
{
  st_expr *newe;
  switch (b->type) {
    case ST_EXPR_TYPE_RNG:
      newe = (st_expr *)malloc(sizeof(st_expr));
      newe->type = ST_EXPR_TYPE_RNG;
      newe->rng = (st_rng_expr_t *)malloc(sizeof(st_rng_expr_t));
      newe->rng->bindvar = strdup(b->rng->bindvar);
      newe->rng->from = st_expr_replace(e, b->rng->bindvar, b->rng->from);
      newe->rng->to = st_expr_replace(e, b->rng->bindvar, b->rng->to);
      return newe;

    case ST_EXPR_TYPE_CONST:
    case ST_EXPR_TYPE_VAR:
      newe = (st_expr *)malloc(sizeof(st_expr));
      if (e->type == ST_EXPR_TYPE_VAR) {
        newe->type = ST_EXPR_TYPE_VAR;
        newe->var = strdup(e->var);
      } else if (e->type == ST_EXPR_TYPE_CONST) {
        newe->type = ST_EXPR_TYPE_CONST;
        newe->num = e->num;
      }
      return newe;

    default:
      fprintf(stderr, "%s:%d %s Not a bind expression (%d)\n", __FILE__, __LINE__, __FUNCTION__, e->type);
  }
  return NULL;
}


st_expr *st_expr_inv(const st_expr *e)
{
  st_expr *newe;
  switch (e->type) {
    case ST_EXPR_TYPE_ADD:
      if (e->bin->right->type != ST_EXPR_TYPE_CONST) return NULL;
      newe = (st_expr *)malloc(sizeof(st_expr));
      newe->type = ST_EXPR_TYPE_SUB;
      newe->bin = (st_bin_expr_t *)malloc(sizeof(st_bin_expr_t));
      newe->bin->left = st_expr_copy(e->bin->left);
      newe->bin->right = st_expr_copy(e->bin->right);
      return newe;

    case ST_EXPR_TYPE_SUB:
      if (e->bin->right->type != ST_EXPR_TYPE_CONST) return NULL;
      newe = (st_expr *)malloc(sizeof(st_expr));
      newe->type = ST_EXPR_TYPE_ADD;
      newe->bin = (st_bin_expr_t *)malloc(sizeof(st_bin_expr_t));
      newe->bin->left = st_expr_copy(e->bin->left);
      newe->bin->right = st_expr_copy(e->bin->right);
      return newe;

    case ST_EXPR_TYPE_MUL:
      if (e->bin->right->type != ST_EXPR_TYPE_CONST) return NULL;
      newe = (st_expr *)malloc(sizeof(st_expr));
      newe->type = ST_EXPR_TYPE_MUL;
      newe->bin = (st_bin_expr_t *)malloc(sizeof(st_bin_expr_t));
      newe->bin->left = st_expr_copy(e->bin->left);
      newe->bin->right = st_expr_copy(e->bin->right);
      return newe;

    case ST_EXPR_TYPE_DIV:
      if (e->bin->right->type != ST_EXPR_TYPE_CONST) return NULL;
      newe = (st_expr *)malloc(sizeof(st_expr));
      newe->type = ST_EXPR_TYPE_MUL;
      newe->bin = (st_bin_expr_t *)malloc(sizeof(st_bin_expr_t));
      newe->bin->left = st_expr_copy(e->bin->left);
      newe->bin->right = st_expr_copy(e->bin->right);
      return newe;

    case ST_EXPR_TYPE_MOD:
    case ST_EXPR_TYPE_SHL:
    case ST_EXPR_TYPE_SHR:
    case ST_EXPR_TYPE_SEQ:
    case ST_EXPR_TYPE_RNG:
      return NULL; // No inverse

    case ST_EXPR_TYPE_VAR:
      newe = (st_expr *)malloc(sizeof(st_expr));
      newe->type = ST_EXPR_TYPE_VAR;
      newe->var = strdup(e->var);
      return newe;

    case ST_EXPR_TYPE_CONST:
      fprintf(stderr, "%s:%s:%d Attempting find inverse for constant/variable!!\n", __FUNCTION__, __FILE__, __LINE__);
      return NULL;

    default:
      fprintf(stderr, "%s:%d %s Unknown expr type: %d\n", __FILE__, __LINE__, __FUNCTION__, e->type);
      return NULL;
  }
}
