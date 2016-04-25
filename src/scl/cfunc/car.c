
#include <stdlib.h>
#include <stdio.h>

#include "../scl.h"
#include "../cfunc.h"

// (car '(a b c)) => 'a
VAL *car(ND *n) {
  if (n->head->type != NODE) {
    fprintf(stderr, ":: car: Not a list.\n");
    exit(5);
  }

  return n->head->val.n->head;
}
