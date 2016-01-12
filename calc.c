/* calc.c

   This file defines all functions
   that have to do with working with
   the NUM struct (see calc.h). */

#include "sc.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stddef.h>

/* SUMMATION

   Sum of n1 and n2. Will
   return NULL, if either is
   NULL */

NUM *sum(NUM *n1, NUM *n2) {
    if (n1 == NULL ||
	n2 == NULL)
	return NULL;
    
    NUM *n = malloc(sizeof(NUM));
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
    
    NUM *n = malloc(sizeof(NUM));
    n->num = n1->num * n2->num;
  
    return n;  
}

/* POWER

   n1 to the power of n2. Will
   return NULL, if either is
   NULL*/

NUM *rpow(NUM *n1, NUM *n2) {
    if (n1 == NULL ||
	n2 == NULL)
	return NULL;
        
    NUM *n = malloc(sizeof(NUM));
    n->num = powl(n1->num, n2->num);
    
    return n;
}
