
#include <stdlib.h>
#include <stdio.h>

#include "../scl.h"
#include "../cfunc.h"
#include "../vtree.h"
#include "../snode.h"

// (def x 32) => [define varaib]
// (def (f x, y, ...) ...) => [define function]
VAL *def(ND *n) {
  VAL *v;
  char *key;
  if (n->head->type == VARIAB) { // variab
    key = n->head->val.s;
    v = eval(n->tail);
  } else if (n->head->type == NODE) { // func
    if (n->head->val.n->head->type != VARIAB) {
      fprintf(stderr, ":: def: invalid def name\n");
      exit(5);
    }

    key = n->head->val.n->head->val.s;
    LBD *l = (LBD *) calloc(1, sizeof(LBD));
    for (ND *m = n->head->val.n->tail;
	 m != NULL;
	 m = m->tail)
      l->pcount++;
	
    l->params = (char **) calloc(l->pcount, sizeof(char*));
    char **p = l->params;
	
    for (ND *m = n->head->val.n->tail;
	 m != NULL;
	 m = m->tail) {
      if (m->head->type == VARIAB)
	*(p++) = m->head->val.s;
      else { // invalid syntax: arguments may only be vars
	fprintf(stderr,":: def: parameter contained non-variable:\n");
	printnode(stderr, m, 0);
	fprintf(stderr, "\n");
	exit(5);
      }
    }
    l->body = n->tail;

    v = (VAL *) calloc(1, sizeof(VAL));
    v->type = LFUNC;
    v->val.l = l;
  } else {
    fprintf(stderr, ":: def: invalid def syntax\n");
    exit(5);
  }
  put_v(n->parent->parent, v, key); // put outsite (def ...
  return NULL;
}
