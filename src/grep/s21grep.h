#ifndef S21GREP_H
#define S21GREP_H

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_grep {
  char *target_files[1000];
  char *templates[1000];
  short i;
  short v;
  short c;
  short l;
  short n;
  short h;
  short s;
  short o;
} t_grep;

int parse_arg(char **argv, t_grep *main_struct);
int exec_grep(t_grep main_struct);

char **get_data_from_file(char *filename, int not_need_print_error);
void add_str_to_array(char *str, char **array);
char *substring(char *string, int position, int length);

#endif