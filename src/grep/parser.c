#include "s21grep.h"

int flag_f(char *filename, t_grep *main_struct);
void flag_e(char *templ, t_grep *main_struct);
void flag_bool(char *flags, t_grep *main_struct);

int parse_arg(char **argv, t_grep *main_struct) {
  for (int i = 1; argv[i] != NULL; i++) {
    if (argv[i][0] == '-') {
      if (strcmp("-f", argv[i]) == 0) {
        i++;
        if (argv[i] == NULL) {
          printf("ключ должен использоваться с аргументом — «f»");
          return 1;
        }
        if (flag_f(argv[i], main_struct) == 1) {
          return 1;
        }
      } else if (strcmp("-e", argv[i]) == 0) {
        i++;
        if (argv[i] == NULL) {
          printf("ключ должен использоваться с аргументом — «e»");
          return 1;
        }
        flag_e(substring(argv[i], 0, strlen(argv[i])), main_struct);
      } else {
        flag_bool(argv[i] + 1, main_struct);
      }
    }
  }

  for (int i = 1; argv[i] != NULL; i++) {
    if (strcmp("-f", argv[i]) == 0 || strcmp("-e", argv[i]) == 0) {
      i++;
      continue;
    } else if (argv[i][0] != '-') {
      if (main_struct->templates[0] != NULL) {
        add_str_to_array(argv[i], main_struct->target_files);
      } else {
        add_str_to_array(substring(argv[i], 0, strlen(argv[i])),
                         main_struct->templates);
      }
    }
  }

  return 0;
}

int flag_f(char *filename, t_grep *main_struct) {
  char **data = get_data_from_file(filename, 0);
  if (data == NULL) {
    return 1;
  }

  for (int i = 0; data[i] != NULL; i++)
    add_str_to_array(data[i], main_struct->templates);

  free(data);

  return 0;
}

void flag_e(char *templ, t_grep *main_struct) {
  add_str_to_array(templ, main_struct->templates);
}

void flag_bool(char *flags, t_grep *main_struct) {
  for (int i = 0; flags[i] != '\0'; i++) {
    if (flags[i] == 'i') {
      main_struct->i = 1;
    } else if (flags[i] == 'v') {
      main_struct->v = 1;
    } else if (flags[i] == 'c') {
      main_struct->c = 1;
    } else if (flags[i] == 'l') {
      main_struct->l = 1;
    } else if (flags[i] == 'n') {
      main_struct->n = 1;
    } else if (flags[i] == 'h') {
      main_struct->h = 1;
    } else if (flags[i] == 's') {
      main_struct->s = 1;
    } else if (flags[i] == 'o') {
      main_struct->o = 1;
    }
  }
}
