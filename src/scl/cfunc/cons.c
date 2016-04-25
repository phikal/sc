
#include <stdlib.h>

#include "../scl.h"
#include "../cfunc.h"

// (cons 'a '(c d)) => '(a b c)
VAL *cons(ND *n) {
  VAL *v = (VAL *) calloc(1, sizeof(VAL));
  v->type = NODE;
  if (n->tail->head->type != NODE) {
    v->val.n = n;
  } else {
    ND *m = (ND *) calloc(1, sizeof(ND));
    m->head = n->head;
    m->tail = n->tail->head->val.n;
    v->val.n = m;
  }
  return v;
}
