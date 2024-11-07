CC = gcc
FLAGS = -std=c11 -Wall -Werror -Wextra

s21_grep:
	$(CC) $(FLAGS) s21_grep.c -o s21_grep

test:
	bash my_test_for_grep.sh

clean:
	rm -rf s21_grep *.o
