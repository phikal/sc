#include <stdlib.h>
#include <stdio.h>

#include "stack.h"


/* ARGV to STACK

   Transforms argv + length into
   STACK struct */

STACK *argvtostack(char **argv, int argc) {
  STACK *s = NULL;
  for (int i = 0; i < argc; i++)
    push(&s, strtonum(argv[i]));
  return s;
}

/* POP

   Pops the first item of of a stack
   and returns it.

   The STACK is afterwards modified */

NUM *pop(STACK **s) {
  if (*s == NULL) return NULL;
  NUM *n = malloc(sizeof(NUM));
  n = (*s)->item;
  *s = (*s)->post;
  return n;
}

/* PUSH

   Adds NUM to beginning of a
   STACK.

   If STACK is NULL, new STACK
   will be created with NUM */

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
