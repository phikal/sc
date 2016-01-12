/* num.h

   header file for num.c */

#include "op.h"

#include <stdint.h>

typedef struct number NUM;

struct number {
    int8_t type;
    double long num;
};

int isnumber(char *s);

NUM *ftonum(long double d);
NUM *itonum(int64_t i);
NUM *strtonum(char *s);

void prnum(NUM *n);
