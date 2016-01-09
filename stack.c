#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

STACK *argvtostack(char **argv, int argc) {
  static STACK s;
  for (int i = 0; i < argc; i++) {
    NUM *n = strtonum(argv[i]);
    push(&s, n);
  }
  return &s;
}

NUM *pop(STACK * s) {
  if (s == NULL)
    return NULL;
  
  if (s->post == NULL) {
    NUM *r = s->item;
    STACK **i = &s;
    i = NULL;
    return r;
  }
  
  while (s->post->post != NULL)
    s = s->post;
  NUM *r = s->post->item;
  s->post = NULL;
  return r;
}

void push(STACK *s, NUM *n) {
  if (s->item == NULL) {
     s->item = n;
  } else {
    STACK *f = malloc(sizeof(STACK));
    f->item = n;
    while (s->post != NULL)
      s = s->post;
    s->post = f;
  }
}
