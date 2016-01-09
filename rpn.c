#include <string.h>

#include <stdio.h>

#include "rpn.h"

#define NEGATIVE itonum(-1)
#define HALF ftonum(0.5)

NUM *rpsi(STACK *s) {
  NUM *r;
  NUM *i = pop(s);

  if (i == NULL)
    return NULL;

  switch (i->type) {
  case ADD:
    r = sum(rpsi(s),
	    rpsi(s));
    break;
  case SUB:
    r = sum(rpsi(s),
	    mul(rpsi(s),
		NEGATIVE));
    break;
  case MUL:
    r = mul(rpsi(s),
	    rpsi(s));
    break;
  case DIV:
    r = mul(rpsi(s),
	    rpow(rpsi(s),
		 NEGATIVE));
    break;
  case POW:
    r = rpow(rpsi(s),
	     rpsi(s));
    break;
  case SQR:
    r = rpow(rpsi(s),
	     HALF);
    break;
  case INV:
    r = rpow(rpsi(s),
	     NEGATIVE);
    break;
  case NRM:
    r = i;
  }

  return r;
}