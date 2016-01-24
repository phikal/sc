/* CALC TESTS

   Tests for testing numbers
   and calculations */

#include "../sc.h"
#include <stdio.h>

int main() {
  NUM *n1 = itonum(1),
    *n2 = ftonum(3.2),
    *n3 = itonum(43),
    *n4 = strtonum("4"),
    *n5 = strtonum("-12.3");

  int c = 0;
  printf("t1: %d\n", c += (n2->num == n1->num + 2.2));
  printf("t2: %d\n", c += (n5->num == -12.3));
  printf("t3: %d (%Lf)\n",
	 c += (rpow(n3, n4)->num == 3418801),
	 rpow(n3, n4)->num);
  printf("t4: %d (%Lf)\n",
	 c += (mul(n2, n4)->num == 12.8),
	 mul(n2, n4)->num);
  printf("t4: %d\n", c += (sum(n1, n5)->num == -11.3));
  printf("t5: %d\n", c += (fact(n4)->num == 24));
  printf("t6: %d\n", c += isnumber("32"));
  printf("t7: %d\n", c += !isnumber("abc"));
  printf("t9: %d\n", c += (gcd(itonum(42), itonum(66))->num == 6));
  // random tests omitted
  printf("t9: %d\n", c += (rfloor(n2)->num == 3));
  printf("t10: %d\n", c += (rceil(n2)->num == 3));
  printf("t11: %d\n", c += (rround(n5)->num == -12));
  printf("t12: %d\n", c += (mod(n3, n4)->num == 3) );

  printf("test sum: %d -> \033[3%s\033[0m\n", c, (c == 12 ? "2mpassed" : "1mfailed"));
}
