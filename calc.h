#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "op.h"

typedef struct number NUM;

struct number {
  int8_t type;
  double long num;
};

NUM *ftonum(long double d);
NUM *itonum(int64_t i);
NUM *strtonum(char *s);

NUM *sum(NUM *n1, NUM *n2);
NUM *mul(NUM *n1, NUM *n2);
NUM *rpow(NUM *n1, NUM *n2);

void prnum(NUM *n);
int isnumber(char *s);
