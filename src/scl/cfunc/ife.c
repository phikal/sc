
#include <stdlib.h>

#include "../scl.h"
#include "../cfunc.h"

// (If [true] ([a]) ([b])) => [a. evaluated]
VAL *ife(ND *n) {
  ND *tru = n->tail,
    *fal = (n->tail == NULL ? NULL :n->tail->tail);

  if (eval(n)->val.v)
    return eval(tru);
  return eval(fal);
}
