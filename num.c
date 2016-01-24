
#include "sc.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "op.h"

#define is(str) if (strcmp(s, str) == 0) return

/* GET TYPE

   Interprets STRING and returns
   type as defined in op.h.

   -1 is returned if operator
   doesn't exist. */

unsigned char gettype(const char *s) {
    if (strlen(s) == 1) switch (s[0]) {
	case '+': return ADD;
	case '-': return SUB;
	case 'x': return MUL;
	case '/': return DIV;
	case '^': return POW;
	case 's': return SQR;
	case 'i': return INV;
	case 'n': return NEG;
	case '!': return FAC;
	case 'f': return FLR;
	case 'r': return ROU;
	case 'c': return CEI;
	}
    is("gcd") GCD;
    is("rnd") RND;
    is("rand") RAN;
    is("mod") MOD;
    return -1;
}


/* IS NUMBER

   Checks if STRING is a number,
   and returns a boolean value. */

bool isnumber(char *s) {
    if (*s == '-' && strlen(s) == 1) return 0;
    for (int i = 0; i < (int) strlen(s); i++)
	if (!(isdigit(s[i]) ||
	      s[i] == '.' ||
	      s[i] == '-'))
	    return 0;
    return 1;
}

/* STRING TO NUMBER */

NUM *strtonum(char *s) {
    NUM *n = calloc(1, sizeof(NUM));
    
    if (isnumber(s)) {
	n->type = NRM;
	n->num = strtod(s, NULL);
	return n;
    }

    if ((n->type = gettype(s)) == -1) {
	printf("error: invalid operator %s\n", s);
	return NULL;
    }

    return n;
}

/* INT TO NUMBER (+vv)

   Allocates new NUM and inserts
   value of int64_t, and vice versa */

NUM *itonum(int64_t i) {
    NUM *n = malloc(sizeof(NUM));
    n->num = (double long) i;
    return n;
}

int64_t numtoi(NUM *n) {
    return (int64_t) n->num;
}

/* FLOAT TO NUMBER (+vv)

   Allocates new NUM and inserts
   value of long double, and vice versa */

NUM *ftonum(long double d) {
    NUM *n = malloc(sizeof(NUM));
    n->num = d;
    return n;
}

long double numtof(NUM *n) {
    return n->num;
}

/* PRINT NUMBER

   Self expiatory */

void prnum(NUM *n) {
    printf("%Lf\n", n->num);
}
