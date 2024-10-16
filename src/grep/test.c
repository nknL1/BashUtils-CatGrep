#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_TEST 15

int main() {
  char test_cases[NUMBER_OF_TEST][100] = {
      "'clean' Makefile",            //
      "-e 'all' -e all Makefile",    //  Шаблон
      "-e 'clean' -e all Makefile",  //
      "-i ALL Makefile",  //  Игнорирует различия регистра
      "-iv ALL Makefile",  //  Игнорирует различия регистра + Инвертирует смысл
                           //  поиска соответствий

      "-ivc ALL Makefile",  //  Игнорирует различия регистра + Инвертирует смысл
                            //  поиска соответствий + Выводит только количество
                            //  совпадающих строк.
      "-c all Makefile",  //  Выводит только количество совпадающих строк.
      "-c ALL Makefile Makefile",  //  Выводит только количество совпадающих
                                   //  строк.
      "-l all Makefile Makefile",  //  Выводит только совпадающие файлы.
      "-inc ALL Makefile Makefile",  //  Игнорирует различия регистра +
                                     //  Предваряет каждую строку вывода номером
                                     //  строки из файла ввода. + Выводит только
                                     //  количество совпадающих строк.
      "-nch all Makefile Makefile",  //  Предваряет каждую строку вывода номером
                                     //  строки из файла ввода + Выводит только
                                     //  количество совпадающих строк + Выводит
                                     //  совпадающие строки, не предваряя их
                                     //  именами файлов
      "-hs all Makefile Makefilezzzzz",  //  Выводит совпадающие строки, не
                                         //  предваряя их именами файлов +
                                         //  Подавляет сообщения об ошибках о
                                         //  несуществующих или нечитаемых
                                         //  файлах.
      "-f try_m try_m",  //  Получает регулярные выражения из файла.
      "-e all -o Makefile",  //  Шаблон + Печатает только совпадающие (непустые)
                             //  части совпавшей строки.
      "all Makefile"         //

  };  // 15

  char s21_grep[200], grep[200];

  for (size_t i = 0; i < NUMBER_OF_TEST; i++) {
    sprintf(s21_grep, "./s21_grep %s > s21_grep.log", test_cases[i]);
    sprintf(grep, "grep %s > grep.log", test_cases[i]);

    system(s21_grep);
    system(grep);

    if (system("diff grep.log s21_grep.log") == 0)
      printf("TEST №%ld SUCCESS\n", i);
    else
      printf("TEST №%ld FAIL\n", i);
  }

  system("rm -f grep.log s21_grep.log");
}