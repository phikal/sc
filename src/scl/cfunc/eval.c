
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../scl.h"
#include "../cfunc.h"
#include "../vtree.h"

VAL *eval(ND *n) { // eval node
  if (n == NULL || n->head == NULL)
    return NULL;
  switch (n->head->type) {
  case NODE: { // if is a list, eval by function name
    VAL *r; // result to return if tail null
    switch (n->head->val.n->head->type) {
    case CFUNC:
      r = n->head->val.n->head->val.f(n->head->val.n->tail);
      break;
    case LFUNC: {
      ND *b = n->head->val.n->head->val.l->body; // body
      int i = 0;
      for (ND *m = n->head->val.n->tail;
	   m != NULL && i < n->head->val.n->head->val.l->pcount;
	   m = m->tail, i++)
	put_v(b, eval(m), n->head->val.n->head->val.l->params[i]);
      r = eval(b);
      break;
    }
    case NODE:
      eval(n->head->val.n);
      r = eval(n->head->val.n->tail);
      break;
    case VARIAB: {
      char *vn = n->head->val.n->head->val.s;
      if ((n->head->val.n->head = get(n, vn)) == NULL) {
	fprintf(stderr, ":: eval: void variable definition: %s\n", vn);
	exit(5);
      }
      return eval(n);
    }
    default:
      fprintf(stderr, ":: eval: First item of evaluated list not function.\n");
      exit(5);
    }
    return n->tail == NULL ? r : eval(n->tail);
  }
  case VARIAB: {
    VAL *v = get(n, n->head->val.s);
    if (v == NULL) {
      fprintf(stderr, ":: eval: var `%s` not defined.\n", n->head->val.s);
      exit(5);
    }
    return v;
  }
    
  default:
    return n->head;
  }
}
