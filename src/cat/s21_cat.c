#include "s21_cat.h"

void flag_b(FILE *file) {
  char line[1000];
  int count = 0;
  int count_f = 0;
  int total_lines = 0;

  while (fgets(line, sizeof(line), file)) {
    total_lines++;
  }
  fseek(file, 0, SEEK_SET);
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0';
    count_f++;
    if (strlen(line) > 0) {
      count++;
      printf("     %d	%s", count, line);
    } else {
      printf("%s", line);
    }
    if (count_f < total_lines) {
      printf("\n");
    }
  }
}
void flag_n(FILE *file) {
  char line[1000];
  int count = 0;
  int count_f = 0;
  int total_lines = 0;
  while (fgets(line, sizeof(line), file)) {
    total_lines++;
  }
  fseek(file, 0, SEEK_SET);
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0';
    count++;
    count_f++;
    if (count_f < 10) {
      printf("     %d	%s", count, line);
    } else {
      printf("    %d	%s", count, line);
    }
    if (count_f < total_lines) {
      printf("\n");
    }
  }
}

int get_flags(char *argv, Flag *flags) {
  int status = 1, end_of_argv = strlen(argv);
  for (int i = 1; i < end_of_argv; i++) {
    if (argv[i] == 's')
      flags->s = 1;
    else if (argv[i] == 'n')
      flags->n = 1;
    else if (argv[i] == 'b')
      flags->b = 1;
    else if (argv[i] == 't') {
      flags->t = 1;
      flags->v = 1;
    } else if (argv[i] == 'T')
      flags->t = 1;
    else if (argv[i] == 'e') {
      flags->e = 1;
      flags->v = 1;
    } else if (argv[i] == 'E')
      flags->e = 1;
    else if (argv[i] == 'v')
      flags->v = 1;
    else {
      fprintf(stderr,
              "cat: illegal option -- %c\nusage: cat [-benstuv] [file ...]\n",
              argv[i]);
      status = 0;
    }
  }
  return status;
}

int get_text_flags(int argc, char **argv, Flag *flags) {
  int status = 1;
  for (int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "--squeeze-blank") || !strcmp(argv[i], "--number") ||
        !strcmp(argv[i], "--number-nonblank")) {
      if (!strcmp(argv[i], "--squeeze-blank"))
        flags->s = 1;
      else if (!strcmp(argv[i], "--number"))
        flags->n = 1;
      else
        flags->b = 1;
    } else if (argv[i][0] == '-') {
      if (!get_flags(argv[i], flags)) {
        status = 0;
        break;
      }
    }
  }
  return status;
}

void cat_function(FILE *file, Flag *flag) {
  for (char ch = '0'; (ch = fgetc(file)) != EOF;) {
    if ((flag->pre_last_char == '\n') && flag->last_char == '\n' &&
        ch == '\n' && flag->s) {
      continue;
    }
    if (flag->t && ch == '\t') {
      printf("^");
      ch = 'I';
    }
    if (flag->e && ch == '\n') {
      printf("$");
    }
    if (flag->v) {
      if (ch < 32 && ch != 9 && ch != 10) {
        ch += 64;
        printf("^");
      }
      if (ch == 127) {
        ch -= 64;
        printf("^");
      }
    }
    flag->pre_last_char = flag->last_char;
    flag->last_char = ch;
    printf("%c", ch);
  }
  fclose(file);
}

int main(int argc, char **argv) {
  FILE *file;
  if (argc > 1) {
    Flag flags = {0, 0, 0, 0, 0, 0, '\0', '\n'};
    if (get_text_flags(argc, argv, &flags)) {
      for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') continue;
        if (flags.b == 1) {
          for (int i = 2; i < argc; i++) {
            file = fopen(argv[i], "r");
            if (file == NULL) {
              printf("Не удалось открыть файл %s.\n", argv[i]);
              continue;
            }
            flag_b(file);
            fclose(file);
          }
          break;
        }
        if (flags.n == 1) {
          for (int i = 2; i < argc; i++) {
            file = fopen(argv[i], "r");
            if (file == NULL) {
              printf("Не удалось открыть файл %s.\n", argv[i]);
              continue;
            }
            flag_n(file);
            fclose(file);
          }
          break;
        }
        FILE *file = fopen(argv[i], "r");
        if (file)
          cat_function(file, &flags);
        else
          fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
      }
    }
  }
}