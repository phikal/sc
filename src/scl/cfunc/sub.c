
#include <stdlib.h>
#include <stdio.h>

#include "../scl.h"
#include "../cfunc.h"

// (- 7 4 2) => 1
VAL *sub(ND *n) { // subtract
  VAL *v = eval(n);
  if (v == NULL) return NULL;
  if (v->type != SCALAR) {
    fprintf(stderr, ":: sub: not all values are scalars\n");
    exit(5);
  }
    
  long double r = v->val.v;
  n = n->tail;
  for (ND *m = n; m != NULL; m = m->tail) {
    v = eval(m); 
    if (v == NULL) return NULL;
    if (v->type != SCALAR) {
      fprintf(stderr, ":: sub: not all values are scalars\n");
      exit(5);
    }
    r -= v->val.v;
  }
    
  v = (VAL *) calloc(1, sizeof(VAL));
  v->type = SCALAR;
  v->val.v = r;
  return v;
}
