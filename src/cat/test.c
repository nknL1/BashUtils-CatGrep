#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_TEST 8

int main() {
  char test_cases[NUMBER_OF_TEST][100] = {
      "Makefile", "Makefile try_22", "Makefile try_22 try_23",
      "-b Makefile",  // нумерует только непустые строки
      // "--number-nonblank Makefile",  // нумерует только непустые строки
      "-e Makefile ",  // отображает символы конца строки как $
      //"--number Makefile",  // нумерует все выходные строки
      "-n Makefile",  // нумерует все выходные строки
      "-s Makefile",  // сжимает несколько смежных пустых строк
      //"--squeeze-blank Makefile",  // сжимает несколько смежных пустых строк
      "-t Makefile",  // также отображает табы как ^I
  };

  char s21_cat[200], cat[200];

  for (size_t i = 0; i < NUMBER_OF_TEST; i++) {
    sprintf(s21_cat, "./s21_cat %s > s21_cat.log", test_cases[i]);
    sprintf(cat, "cat %s > cat.log", test_cases[i]);

    system(s21_cat);
    system(cat);

    if (system("diff cat.log s21_cat.log") == 0)
      printf("TEST №%ld SUCCESS\n", i);
    else
      printf("TEST №%ld FAIL\n", i);
  }

  system("rm -f cat.log s21_cat.log");
}