
#include <stdlib.h>

#include "../scl.h"
#include "../cfunc.h"

// (= 32 16 8 ...) => 0
VAL *eqp(ND *n) {
  VAL *r = (VAL *) calloc(1, sizeof(VAL));
  r->type = SCALAR;
  r->val.v = 1;

  VAL *v = n->head;
  ND *m = n;
  while ((m = m->tail) != NULL)
    if (v->val.n != m->head->val.n) {
      r->val.v = 0;
      break;
    }
  
  return r;
}
