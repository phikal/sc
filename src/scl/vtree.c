
#include <string.h>
#include <stdlib.h>

#include "scl.h"
#include "vtree.h"

// VALUE TREE
VAL *get_vt(VT *tr, char *key) {
  if (tr != NULL) {
    if (strcmp(key, tr->name) == 0)
      return tr->val;
    else if (strcmp(key, tr->name) >  0)
      return get_vt(tr->l_val, key);
    else if (strcmp(key, tr->name) <  0)
      return get_vt(tr->r_val, key);
  } return NULL;
}

VAL *get(ND *n, char *key) {
  if (n->varib == NULL)
    return get(n->parent, key);
  else {
    VAL *v = get_vt(n->varib, key);
    return ((v != NULL || n == n->parent) ? v : get(n->parent, key));
  }
}

VT *put(VT *tr, VAL *val, char *key) {
  if (tr == NULL) {
    tr = (VT *) calloc(1,  sizeof(VT));
    tr->name = key;
  }

  if (strcmp(tr->name, key) == 0)
    tr->val = val;
  else if (strcmp(tr->name, key) < 0)
    tr->l_val = put(tr->l_val, val, key);
  else if (strcmp(tr->name, key) > 0)
    tr->r_val = put(tr->r_val, val, key);
  return tr;
}

void put_v(ND *n, VAL *val, char *key) {
  n->varib = put(n->varib, val, key);
}

void put_sc(ND *n, double val, char *key) {
  VAL *v = (VAL *) calloc(1, sizeof(VAL));
  v->type = SCALAR;
  v->val.v = val;
  n->varib = put(n->varib, v, key);
}

void put_nd(ND *n, ND *val, char *key) {
  VAL *v = (VAL *) calloc(1, sizeof(VAL));
  v->type = NODE;
  v->val.n = val;
  n->varib = put(n->varib, v, key);
}

void put_sym(ND *n, char *val, char *key) {
  VAL *v = (VAL *) calloc(1, sizeof(VAL));
  v->type = SYMBOL;
  v->val.s = val;
  n->varib = put(n->varib, v, key);
}

void put_cf(ND *n, FUNC *val, char *key) {
  VAL *v = (VAL *) calloc(1, sizeof(VAL));
  v->type = CFUNC;
  v->val.f = val;
  n->varib = put(n->varib, v, key);
}

void put_lf(ND *n, ND *val, char *key) {
  VAL *v = (VAL *) calloc(1, sizeof(VAL));
  v->type = LFUNC;
  v->val.n = val;
  n->varib = put(n->varib, v, key);
}

void put_var(ND *n, char *val, char *key) {
  VAL *v = calloc(1, sizeof(VAL));
  v->type = VARIAB;
  v->val.s = val;
  n->varib = put(n->varib, v, key);
}
