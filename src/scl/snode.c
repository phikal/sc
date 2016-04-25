
#include <stdio.h>
#include "scl.h"
#include "snode.h"

void printvtree(FILE *f, VT *t, int ind) {
  if (t == NULL) return;
  for (int i = 0; i < ind; i++) fprintf(f, " ");
  fprintf(f, "%s:\t",t->name);
  printval(f, t->val, ind);
  fprintf(f, ",\n");
  printvtree(f, t->l_val, ind+1);
  printvtree(f, t->r_val, ind+1);
}

void printnode(FILE *f, ND *n, int ind) {
  if (n == NULL)
    return printval(f, NULL, ind);

  if (n->varib != NULL) {
    fprintf(f, "{\n");
    printvtree(f, n->varib, ind+3);
    for (int i = 1; i < ind; i++) fprintf(f, "  ");
    fprintf(f, "} ");
  }
  
  if (n->head == NULL && n->tail == NULL)
    fprintf(f, "x - ");
  else if (n->head != NULL && n->head->type == NODE)
    fprintf(f, "O - ");
  else
    fprintf(f, "o - ");

  printval(f, n->head, ind+1);
  fprintf(f, "\t(%p)\n", n);

  for (int i = 0; i < ind; i++) fprintf(f, "  ");
  fprintf(f, "L ");
  if (n->tail != NULL)
    printnode(f, n->tail, ind+1);
  else
    printval(f, NULL, ind);
}

void printval(FILE *f, VAL *v, int ind) {
  if (v == NULL) {
    fprintf(f, "NULL");
    return;
  }
  else if (v->type == SCALAR)
    fprintf(f, "%Lf", v->val.v);
  else if (v->type == NODE)
    printnode(f, v->val.n, ind+1);
  else if (v->type == CFUNC)
    fprintf(f, "[cfunc]");
  else if (v->type == LFUNC) {
    fprintf(f, "[lfunc]:\n  ");
    printnode(f, v->val.l->body, ind+1);
  } else if (v->type == SYMBOL)
    fprintf(f, "'%s", v->val.s);
  else if (v->type == VARIAB)
    fprintf(f, "`%s` ", v->val.s);
  else fprintf(f, "INVALID");
  //  fprintf(f, "\t(%p)", v);
}

