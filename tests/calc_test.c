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

  printf("t1: %d\n", (n2->num == n1->num + 2.2));
  printf("t2: %d\n", (n5->num == -12.3));
  printf("t3: %d (%Lf)\n",
	 (rpow(n3, n4)->num == 3418801),
	 rpow(n3, n4)->num);
  printf("t4: %d (%Lf)\n",
	 (mul(n2, n4)->num == 12.8),
	 mul(n2, n4)->num);
  printf("t4: %d\n", (sum(n1, n5)->num == -11.3));
  printf("t5: %d\n", (fact(n4)->num == 24));
  printf("t6: %d\n", isnumber("32"));
  printf("t7: %d\n", !isnumber("abc"));
  
}
