#include <stdio.h>

#include "rpn.h"

int help(char *bin, int e) {
  if (e == 1)
    fprintf(stderr, "usage: %s [rpn syntax calculation]\n", bin);
  else if (e == 2)
    fprintf(stderr, "%s: invalid stack\n", bin);
  return e;
}

int main(int argc, char *argv[]) {
  if (argc == 1)
    return help(argv[0], 1);

  STACK *s = argvtostack(argv+1, argc-1);
  NUM *n = rpsi(&s);
  if (n == NULL)
    return help(argv[0], 2);
  else
    prnum(n);
  
  return 0;
}
