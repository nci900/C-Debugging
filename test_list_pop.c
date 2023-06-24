#include "list2.h"

int main(void) {
  // Make a list of square numbers
  List squares = list_init();
  for (int i = 0; i < 10; ++i)
    list_append(&squares, i*i);
  list_pop(&squares, 3);
  list_print(squares);
  list_print_contents(squares);
  list_destroy(&squares);
  return 0;
}


