#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// char** get_data_from_file(char *filename, int not_need_print_error) {
//     FILE *file = fopen(filename, "r");
//     if (file == NULL) {
//         if (not_need_print_error == 0) {
//             printf("Не удалось открыть файл %s\n", filename);
//         }
//         return NULL;
//     }

//     char **result = (char**)malloc(sizeof(char*) * 1000);
//     char line[256];

//     int i = 0;
//     for (; fgets(line, sizeof(line), file); i++) {
//         size_t len_line = strlen(line);
//         result[i] = (char*)malloc(len_line + 1);
//         strcpy(result[i], line);

//         // delete \n
//         result[i][len_line - 1] = '\0';
//     }

//     result[i] = NULL;

//     fclose(file);

//     return result;
// }

char **get_data_from_file(char *filename, int not_need_print_error) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    if (not_need_print_error == 0) {
      printf("Не удалось открыть файл %s\n", filename);
    }
    return NULL;
  }

  char **result = NULL;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  size_t i = 0;

  while ((read = getline(&line, &len, file)) != -1) {
    // Удаляем \n
    if (line[read - 1] == '\n') {
      line[read - 1] = '\0';
      --read;
    }

    // Расширяем память с помощью realloc
    char **temp = (char **)realloc(result, (i + 1) * sizeof(char *));
    if (temp == NULL) {
      // Обработка ошибки
      printf("Ошибка выделения памяти.\n");
      free(result);
      free(line);
      fclose(file);
      return NULL;
    }
    result = temp;

    result[i] = (char *)malloc(read + 1);
    if (result[i] == NULL) {
      // Обработка ошибки
      printf("Ошибка выделения памяти.\n");
      free(result);
      free(line);
      fclose(file);
      return NULL;
    }

    strcpy(result[i], line);
    i++;
  }

  // Добавляем NULL в конец
  char **temp = (char **)realloc(result, (i + 1) * sizeof(char *));
  if (temp == NULL) {
    // Обработка ошибки
    printf("Ошибка выделения памяти.\n");
    free(result);
    free(line);
    fclose(file);
    return NULL;
  }
  result = temp;
  result[i] = NULL;

  free(line);
  fclose(file);

  return result;
}

void add_str_to_array(char *str, char **array) {
  size_t len = 0;
  while (array[len] != NULL) {
    len++;
  }

  array[len] = str;
  array[len + 1] = NULL;
}

char *substring(char *string, int position, int length) {
  char *result = (char *)malloc(length + 1);
  if (result == NULL) {
    printf("Ошибка выделения памяти.\n");
    return NULL;
  }
  strncpy(result, &string[position], length);
  result[length] = '\0';
  return result;
}