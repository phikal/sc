
#include <stdlib.h>
#include <stdio.h>

#include "../scl.h"
#include "../cfunc.h"

// (> 32 16 8 ...) => 1
VAL *gtp(ND *n) {
  VAL *r = (VAL *) calloc(1, sizeof(VAL));
  r->type = SCALAR;
  r->val.v = 1;

  if (n->head->type != SCALAR) {
    fprintf(stderr, ":: ltp: cannot compare non-scalars\n");
    exit(5);
  }
  
  long double p = eval(n)->val.v;
  ND *m = n;
  while ((m = m->tail) != NULL) {
    VAL *e  = eval(m);
    if (e->type != SCALAR) {
      fprintf(stderr, ":: ltp: cannot compare non-scalars\n");
      exit(5);
    }
    if (p >= e->val.v) {
      r->val.v = 0;
      break;
    }
    p = e->val.v;
  }
  
  return r;
}
