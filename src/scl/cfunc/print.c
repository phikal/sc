
#include <stdlib.h>
#include <stdio.h>

#include "../scl.h"
#include "../cfunc.h"
#include "../snode.h"

// (print [evaluated variable])
VAL *print(ND *n) {
  printval(stdout, eval(n), 0);
  printf("\n");
  return NULL;
}
