
#include <stdlib.h>

#include "../scl.h"
#include "../cfunc.h"

// (and [true] [false]) => [false]
VAL *and(ND *n) {
  VAL *r = (VAL *) calloc(1, sizeof(VAL));
  r->type = SCALAR;
  r->val.v = 1;

  ND *m = n;
  while ((m = m->tail) != NULL)
    if (!eval(m)->val.v) {
      r->val.v = 0;
      break;
    }
  
  return r;
}
