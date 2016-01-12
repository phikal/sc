
#include "op.h"

#include <stdint.h>

/* defined in num.c */
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

/* defined in calc.c */
NUM *sum(NUM *n1, NUM *n2);
NUM *mul(NUM *n1, NUM *n2);
NUM *rpow(NUM *n1, NUM *n2);
NUM *fact(NUM *n1);

/* defined in stack.c */
typedef struct stack STACK;

struct stack {
    NUM *item;
    STACK *post;
};

STACK *argvtostack(char **argv, int argc);

NUM *pop(STACK **s);
void push(STACK **s, NUM *n);

/* defined in rpn.c */
NUM *rpsi(STACK **s);
