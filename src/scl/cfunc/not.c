
#include <stdlib.h>

#include "../scl.h"
#include "../cfunc.h"

// (not [false]) => [true]
VAL *not(ND *n) {
  VAL *r = (VAL *) calloc(1, sizeof(VAL));
  r->type = SCALAR;
  r->val.v = !(eval(n)->val.v);
  return r;
}
