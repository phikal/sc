
#include <stdlib.h>
#include <stdio.h>

#include "../scl.h"
#include "../cfunc.h"

// (+ 2 3 4) => 9
VAL *sum(ND *n) { // suming
  long double r = 0;
  for (ND *m = n; m != NULL; m = m->tail) {
    VAL *v = eval(m);
    if (v == NULL) return NULL;
    if (v->type != SCALAR) {
      fprintf(stderr, ":: sum: not all values are scalars\n");
      exit(5);
    }
    r += v->val.v;
  }
    
  VAL *v = (VAL *) calloc(1, sizeof(VAL));
  v->type = SCALAR;
  v->val.v = r;
  return v;
}
