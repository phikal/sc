/* op.h

   All operator numbers are
   defined in this file. */

#define NRM 0 // normal

#define ADD 1 // addition
#define SUB 2 // subtraction (x+(y*-1))
#define MUL 3 // multiplicaiton
#define DIV 4 // division (x*(y^-1)) or (x * INV(y))
#define POW 5 // power
#define SQR 6 // square root (x^0.5)
#define INV 7 // invert (x^-1)
#define NEG 8 // negative (x*-1)
#define FAC 9 // factorial
#define GCD 10 // greatest common denominator
#define RND 11 // random num from 0 to 1
#define RAN 12 // random num from x to y
#define FLR 13 // floor
#define ROU 14 // round
#define CEI 15 // ceiling
#define MOD 16 // modulo
