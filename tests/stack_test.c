#include "../stack.h"
#include <stdio.h>

void prstack(STACK *s) {
  printf("%Lf,\t%d\n", s->item->num, s->item->type);

  prnum(s->item);
  if (s->post != NULL)
    prstack(s->post);
  else
      printf("===\n");
}

int main() {
  char *argv[] = { "-12", "3", "43", "32.32" };
  STACK *s = argvtostack(argv, 4);

  /* prstack(s); */
  
  NUM *n1 = pop(&s);
  NUM *n2 = pop(&s);

  /* prstack(s); */
  
  NUM *n3 = itonum(28);
  push(&s, n3);

  /* prstack(s); */

  NUM *n4 = pop(&s);
  
  /* prstack(s); */

  pop(&s);
  pop(&s);
  NUM *n5 = pop(&s);
  NUM *n6 = pop(&s);

  /* printf("%Lf\t%p\n", n1->num, &n1->num); */
  /* printf("%Lf\t%p\n", n2->num, &n2->num); */
  /* printf("%Lf\t%p\n", n3->num, &n3->num); */
  /* printf("%Lf\t%p\n", n4->num, &n4->num); */
  
  printf("t1: %d\n", (n4->num == n3->num));
  printf("t2: %d\n", (n2->num == (itonum(43))->num));
  printf("t3: %d\n", (n1->num == (ftonum(32.32))->num));
  printf("t4: %d\n", (n5 == NULL));
  printf("t5: %d\n", (n6 == NULL));
  printf("t6: %d\n", (s == NULL));
  
}
