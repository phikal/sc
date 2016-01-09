#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#include "calc.h"

unsigned char gettype(const char *s) {
  if (strlen(s) == 1) switch (s[0]) {
    case '+': return ADD;
    case '-': return SUB;
    case 'x': return MUL;
    case '/': return DIV;
    case '^': return POW;
    case 's': return SQR;
    case 'i': return INV;
    }
  return -1;
}

int isnumber(char *s) {
  if (*s == '-' && strlen(s) == 1) return 0;
  for (int i = 0; i < (int) strlen(s); i++)
    if (!(isdigit(s[i]) ||
	  s[i] == '.' ||
	  s[i] == '-'))
      return 0;
  return 1;
}

NUM *strtonum(char *s) {
  NUM *n = calloc(1, sizeof(NUM));
    
  if (isnumber(s)) {
    n->type = NRM;
    n->num = strtod(s, NULL);
    return n;
  }

  if ((n->type = gettype(s)) == -1)
    printf("error: invalid operator %s\n", s);
    
  return n;
}

NUM *itonum(int64_t i) {
  NUM *n = malloc(sizeof(NUM));
  n->num = (double long) i;
  return n;
}

NUM *ftonum(long double d) {
  NUM *n = malloc(sizeof(NUM));
  n->num = d;
  return n;
}

NUM *sum(NUM *n1, NUM *n2) {
  if (n1 == NULL ||
      n2 == NULL)
    return NULL;
    
  NUM *n = malloc(sizeof(NUM));
  n->num = n1->num + n2->num;
    
  return n;
}

NUM *mul(NUM *n1, NUM *n2) {
  if (n1 == NULL ||
      n2 ==  NULL)
    return NULL;
    
  NUM *n = malloc(sizeof(NUM));
  n->num = n1->num * n2->num;
  
  return n;  
}

NUM *rpow(NUM *n1, NUM *n2) {
  if (n1 == NULL ||
      n2 == NULL)
    return NULL;
        
  NUM *n = malloc(sizeof(NUM));
  n->num = powl(n1->num, n2->num);
    
  return n;
}

void prnum(NUM *n) {
  printf("%Lf\n", n->num);
}
