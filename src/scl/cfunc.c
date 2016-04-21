
// LISP FUNCTIONS IN C
// ASSUMING OMITTED FUNCTION NAME (cdr'ed)

#include <stdlib.h>
#include <stdio.h>

#include "scl.h"
#include "cfunc.h"

// evaluation

VAL *evalf(ND *n) { // eval node
  return n->head;
}

VAL *loadf(ND *n) {
  return n->head;  
}

// lisp functions

VAL *car(ND *n) { return n->head; }

VAL *cdr(ND *n) {
  VAL *v = calloc(1, sizeof(VAL));
  v->type = NODE;
  v->val.n = n->tail;
}

VAL *cons(ND *n) {
  return n->head;
}

VAL *def(ND *n) {
  return n->head;
}

VAL *lambda(ND *n) {
  return n->head;
}

// arthemetric

VAL *sum(ND *n) { // suming
  return n->head;
}

VAL *sub(ND *n) { // subtract
  return n->head;
}

VAL *fac(ND *n) { // factor
  return n->head;
}

VAL *quo(ND *n) { // quotient
  return n->head;
}

VAL *rem(ND *n) { // remender
  return n->head;
}

// equalities

VAL *eqp(ND *n) {
  return n->head;
}

VAL *ltp(ND *n) {
  return n->head;
}

VAL *gtp(ND *n) {
  return n->head;
}

// logic

VAL *ife(ND *n) {
  return n->head;
}

VAL *and(ND *n) {
  return n->head;
}

VAL *or(ND *n) {
  return n->head;
}

VAL *not(ND *n) {
  return n->head;
}
