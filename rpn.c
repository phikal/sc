/* rpn.c

   This file holds the rpsi function, that
   is used to evaluate a stack, interpret
   it as a tree and return a value. */

#include "sc.h"

#include <stddef.h>

#include "op.h"

#define ZERO itonum(0)
#define ONE itonum(1)
#define NEGATIVE itonum(-1)
#define HALF ftonum(0.5)

/* REVERSED POLISH STACK INTERPRETER

   This function takes the pointer to a pointer
   of a STACK and interprets in tree-wise.

   Returning either a NUM on success (enough elements
   available) or NULL on failure. */

NUM *rpsi(STACK **s) {
    NUM *r = NULL,
	*i = pop(s);

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
    case NEG:
	r = mul(rpsi(s),
		NEGATIVE);
	break;
    case FAC:
	r = fact(rpsi(s));
	break;
    case GCD:
	r = gcd(rpsi(s),
		rpsi(s));
	break;
    case RND:
	r = rndg(ZERO, ONE);
	break;
    case RAN:
	r = rndg(rpsi(s),
		 rpsi(s));
	break;
    case FLR:
	r = rfloor(rpsi(s));
	break;
    case ROU:
	r = rround(rpsi(s));
	break;
    case CEI:
	r = rceil(rpsi(s));
	break;
    case MOD:
	r = mod(rpsi(s),
		rpsi(s));
	break;
    case NRM:
	    r = i;
    }
    
    return r;
}
