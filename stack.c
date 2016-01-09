#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

STACK *argvtostack(char **argv, int argc) {
  STACK *s = NULL;
  for (int i = 0; i < argc; i++)
    push(&s, strtonum(argv[i]));
  return s;
}

NUM *pop(STACK **s) {
  if (*s == NULL) return NULL;
  NUM *n = malloc(sizeof(NUM));
  n = (*s)->item;
  *s = (*s)->post;
  return n;
}

void push(STACK **s, NUM *n) {
  STACK *i = malloc(sizeof(STACK));
  i->item = n;
  i->post = NULL;
  if (s == NULL) *s = i;
  else {
    i->post = *s;
    *s = i;
  }
}
