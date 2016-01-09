#include "calc.h"

typedef struct stack STACK;

struct stack {
  NUM *item;
  STACK *post;
};

STACK *argvtostack(char **argv, int argc);

NUM *pop(STACK **s);
void  push(STACK **s, NUM *n);
