SOURCE=main.c parser.c exec.c tools.c
CC = gcc
FLAGS = -Wall -Wextra -Werror

all: rebuild

s21_grep:
	$(CC) $(FLAGS) $(SOURCE) -o s21_grep

clean:
	rm -f s21_grep

rebuild: clean s21_grep
