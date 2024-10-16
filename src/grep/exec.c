#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21grep.h"

regex_t *comp_templates(char **templates, size_t count_templates, int options);
void clean_compilated_regex(regex_t *compilated_regex, size_t count);

int exec_grep(t_grep main_struct) {
  if (main_struct.v == 1 && main_struct.o == 1) return 0;

  int reg_comp_options = 0;
  if (main_struct.i == 1) {
    reg_comp_options = REG_ICASE;
  }

  size_t count_templates = 0;
  while (main_struct.templates[count_templates]) count_templates++;

  regex_t *compilated_templates =
      comp_templates(main_struct.templates, count_templates, reg_comp_options);
  if (compilated_templates == NULL) return 1;

  for (int i = 0; main_struct.target_files[i]; i++) {
    char **target_data =
        get_data_from_file(main_struct.target_files[i], main_struct.s);
    if (target_data == NULL) {
      continue;
    }

    int count_finds = 0;

    for (int k = 0; target_data[k] != NULL; k++) {
      for (size_t j = 0; j < count_templates; j++) {
        int ret;

        if (main_struct.o == 1 && main_struct.c != 1 && main_struct.l != 1) {
          if (strcmp(main_struct.templates[j], "") ==
              0)  // если пустая строка и -o то скипаем на next
            continue;

          regmatch_t pmatch[1];  // БУДЕТ СОДЕРЖАТЬ ИНДЕКС НАЧАЛА И КОНЦА
                                 // НАЙДЕННОЙ СТРОКИ
          char *ptr = target_data[k];

          while (regexec(&compilated_templates[j], ptr, 1, pmatch, 0) == 0) {
            if (!(main_struct.h == 1 ||
                  (i == 0 && main_struct.target_files[i + 1] == NULL))) {
              printf("%s:", main_struct.target_files[i]);
            }
            if (main_struct.n == 1) {
              printf("%d:", k + 1);
            }
            char *find_chunk = substring(ptr, pmatch[0].rm_so,
                                         pmatch[0].rm_eo - pmatch[0].rm_so);
            if (find_chunk == NULL) {
              clean_compilated_regex(compilated_templates, count_templates);
              return 1;
            }
            printf("%s\n", find_chunk);
            free(find_chunk);
            ptr += pmatch[0].rm_eo;
          }
        } else {
          ret = regexec(&compilated_templates[j], target_data[k], 0, NULL, 0);
          if ((ret == 0 && main_struct.v == 0) ||
              (ret != 0 && main_struct.v == 1)) {
            if (main_struct.c != 1 && main_struct.l != 1) {
              if (!(main_struct.h == 1 ||
                    (i == 0 && main_struct.target_files[i + 1] == NULL))) {
                printf("%s:", main_struct.target_files[i]);
              }
              if (main_struct.n == 1) {
                printf("%d:", k + 1);
              }
              printf("%s\n", target_data[k]);
            }
            count_finds++;
            break;
          }
        }
      }

      if (main_struct.l == 1 && count_finds > 0) {
        printf("%s\n", main_struct.target_files[i]);
        for (size_t m = k; target_data[m] != NULL; m++) free(target_data[m]);
        break;
      }

      free(target_data[k]);
    }

    free(target_data);

    if (main_struct.c == 1 && main_struct.l != 1) {
      if (!(main_struct.h == 1 ||
            (i == 0 && main_struct.target_files[i + 1] == NULL))) {
        printf("%s:", main_struct.target_files[i]);
      }
      printf("%d\n", count_finds);
    }
  }

  clean_compilated_regex(compilated_templates, count_templates);

  return 0;
}

regex_t *comp_templates(char **templates, size_t count_templates, int options) {
  regex_t *regexes = (regex_t *)malloc((count_templates + 1) * sizeof(regex_t));
  if (regexes == NULL) {
    fprintf(stderr, "Ошибка выделения памяти\n");
    return NULL;
  }
  for (size_t i = 0; i < count_templates; i++) {
    int reti = regcomp(&regexes[i], templates[i], options);
    if (reti) {
      fprintf(stderr, "Не удалось скомпилировать регулярное выражение: %s\n",
              templates[i]);
      free(regexes);
      return NULL;
    }
  }

  return regexes;
}

void clean_compilated_regex(regex_t *compilated_regex, size_t count) {
  for (size_t j = 0; j < count; j++) {
    regfree(&compilated_regex[j]);
  }

  free(compilated_regex);
}
