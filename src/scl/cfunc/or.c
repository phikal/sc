
#include <stdlib.h>

#include "../scl.h"
#include "../cfunc.h"

// (or [true] [false]) => [true]
VAL *or(ND *n) {
  VAL *r = (VAL *) calloc(1, sizeof(VAL));
  r->type = SCALAR;
  r->val.v = 0;

  ND *m = n;
  while ((m = m->tail) != NULL)
    if (eval(n)->val.v) {
      r->val.v = 1;
      break;
    }
    
  return r;
}
