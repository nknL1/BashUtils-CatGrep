#ifndef MY_CAT_H
#define MY_CAT_H

#include <stdio.h>
#include <string.h>

typedef struct possible_flags {
  int b, e, n, s, t, v;
  char pre_last_char, last_char;

} Flag;

void print_non_empty_lines(FILE *file);
void print_lines(FILE *file);
int get_flags(char *argv, Flag *flags);
int reading_text_and_char_args(int argc, char **argv, Flag *flags);
void cat_function(FILE *file, Flag *flag);

#endif  // MY_CAT_H
