#include <stdlib.h>

#include "s21grep.h"

void clean(t_grep *main_struct);

int main(int argc, char **argv) {
  (void)argc;
  int ret = 0;
  t_grep main_struct = {0};

  if (parse_arg(argv, &main_struct) == 1)
    ret = 1;
  else
    ret = exec_grep(main_struct);

  clean(&main_struct);

  return ret;
}

void clean(t_grep *main_struct) {
  for (int i = 0; main_struct->templates[i]; i++) {
    free(main_struct->templates[i]);
  }
}
