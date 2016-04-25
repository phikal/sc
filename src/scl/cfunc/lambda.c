
#include <stdlib.h>
#include <stdio.h>

#include "../scl.h"
#include "../cfunc.h"
#include "../vtree.h"

// (lambda (x, y, ...) ...) => [anon. func]
VAL *lambda(ND *n) {
  if (n->head->type == NODE) {
    LBD *l = (LBD *) calloc(1, sizeof(LBD));
    int pcount = 0; // parameter count
    for (ND *m = n->head->val.n; m != NULL; m = m->tail) pcount++;
    char **param = (char **) calloc(pcount, sizeof(char*)),
      **p = param;
    for (ND *m = n->head->val.n; m != NULL; m = m->tail)
      if (m->head->type == VARIAB)
	*(p++) = m->head->val.s;
      else { // invalid syntax: arguments may only be vars
	fprintf(stderr, ":: lambda: parameter contained non-variable\n");
	exit(5);
      }
    l->params = param;
    l->pcount = pcount;
    l->body = n->tail;

    VAL *v = (VAL *) calloc(1, sizeof(VAL));
    v->type = LFUNC;
    v->val.l = l;
    return v;
  } else { // invalid syntax: first element has to be list
    fprintf(stderr, ":: lambda: defined without list as first element\n");
    exit(5);
  }
}
