/* calc.c

   This file defines all functions
   that have to do with working with
   the NUM struct (see calc.h). */

#include "sc.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

#define NUM() malloc(sizeof(NUM))

/* INT OR DECIMAL

   Funcions to check if a
   NUM has decimals or not */

bool isint(NUM *n) {
  return (fmod((n->num),1) == 0);
}

bool isdeci(NUM *n) {
  return !isint(n);
}

/* SUMMATION

   Sum of n1 and n2. Will
   return NULL, if either is
   NULL */

NUM *sum(NUM *n1, NUM *n2) {
    if (n1 == NULL ||
	n2 == NULL)
	return NULL;
    
    NUM *n = NUM();
    n->num = n1->num + n2->num;
    
    return n;
}

/* MULTIPLICATION

   Value of n1 times n2. Will
   return NULL, if either is
   NULL */

NUM *mul(NUM *n1, NUM *n2) {
    if (n1 == NULL ||
	n2 ==  NULL)
	return NULL;
    
    NUM *n = NUM();
    n->num = n1->num * n2->num;
  
    return n;  
}

/* POWER

   n1 to the power of n2. Will
   return NULL, if either is
   NULL */

NUM *rpow(NUM *n1, NUM *n2) {
    if (n1 == NULL ||
	n2 == NULL)
	return NULL;
        
    NUM *n = NUM();
    n->num = powl(n1->num, n2->num);
    
    return n;
}

/* FACTORIAL

   Returns factorial value
   of NUM, if int */

NUM *fact(NUM *num) {
  if (isdeci(num))
    return NULL;

  NUM *res = NUM();
  int64_t val = (int64_t) (res->num = num->num);

  if (val < 1)
    return 0;

  while (--val)
    res->num *= val;

   return res;
}
