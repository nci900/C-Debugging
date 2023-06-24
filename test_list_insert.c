#include "list2.h"

void list_insert(List* list, size_t index, double value) {
  // TODO: Implement list_insert here
}

int main(void) {
  List a = list_init();
  for (int v = 0; v < 6; ++v)
    list_append(&a, v);
  list_insert(&a, 3, 2.5);
  list_pop(&a, 1);

  // Should print [0, 2, 2.5, 3, 4, 5]
  list_print_contents(a);

  list_destroy(&a);
}
