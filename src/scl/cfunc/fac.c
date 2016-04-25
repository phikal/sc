
#include <stdlib.h>
#include <stdio.h>

#include "../scl.h"
#include "../cfunc.h"

// (* 3 2 1) => 6
VAL *fac(ND *n) { // factor
  long double r = 1;
  for (ND *m = n; m != NULL; m = m->tail) {
    VAL *v = eval(m);
    if (v == NULL) return NULL;
    if (v->type != SCALAR) {
      fprintf(stderr, ":: sum: not all values are scalars\n");
      exit(5);
    }
    r *= v->val.v;
  }
    
  VAL *v = (VAL *) calloc(1, sizeof(VAL));
  v->type = SCALAR;
  v->val.v = r;
  return v;
}
