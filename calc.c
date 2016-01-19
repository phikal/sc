/* calc.c

   This file defines all functions
   that have to do with working with
   the NUM struct (see sc.h). */

#include "sc.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>

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

/* COMPARISONS

   Equvalences and unequivalence
   functions all require two
   NUMs, with nither being NULL */

bool eq(NUM *n1, NUM *n2) {
  return n1->num == n2->num;
}

bool neq(NUM *n1, NUM *n2) {
  return !eq(n1, n2);
}

bool lt(NUM *n1, NUM *n2) {
  return n1->num < n2->num;
}

bool gt(NUM *n1, NUM *n2) {
  return n1->num > n2->num;
}

bool let(NUM *n1, NUM *n2) {
  return !gt(n1, n2);
}

bool get(NUM *n1, NUM *n2) {
  return !lt(n1, n2);
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

/* GREATEST COMMON DENOMINATOR

   Calculates the greatest common
   denominator of two integers
   Uses Euclid's Algorithm */

NUM *gcd(NUM *num1, NUM *num2) {
    if (isdeci(num1) ||
	isdeci(num2))
	return NULL;
    
    NUM *res = NUM();
    int64_t a = (int64_t) num1->num,
	b = (int64_t) num2->num,
	h = 0; // holder 

    while (b != 0) {
	h = a;
	a = b;
	b = h % b;
    }

    res->num = a;
    return res;
}

/* RANDOM GENERATOR

   Generates a pseudo-random
   number between two values. */

long int random();
void srandom(unsigned int seed);

NUM *rndg(NUM *num1, NUM *num2) {
    if (num1 == NULL ||
	num2 == NULL ||
	get(num1, num2))
	return NULL;

    srandom((long int) abs((long int)&num1+getpid()));

    double long n1 = numtof(num1),
      n2 = numtof(num2);
    return ftonum((random()/(double) RAND_MAX*(n1-n2))+n2);
}

/* INTEGER APPROXIMATIONS

   The following functions are used
   to approximte int values for floating
   point values. */

NUM *rfloor(NUM *num) {
  if (num == NULL)
    return NULL;

  return itonum(floorl(numtof(num)));
}

NUM *rround(NUM *num) {
  if (num == NULL)
    return NULL;

  return itonum(rintl(numtof(num)));
}

NUM *rceil(NUM *num) {
  if (num == NULL)
    return NULL;

  return itonum(ceill(numtof(num)));
}
