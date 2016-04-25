
#include <stdlib.h>
#include <stdio.h>

#include "../scl.h"
#include "../cfunc.h"

// (cdr '(a b c)) => '(b c)
VAL *cdr(ND *n) {
  if (n->head->type != NODE) {
    fprintf(stderr, ":: cdr: Not a list.\n");
    exit(5);
  }

  VAL *v = (VAL *) calloc(1, sizeof(VAL));
  v->type = NODE;
  v->val.n = n->head->val.n->tail;
  return v;
}
