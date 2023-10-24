CC = gcc
CFLAGS = -Wall -Wextra -Werror 

all: clean s21_grep

s21_grep: grep.c grep.h
	$(CC) $(CFLAGS) grep.c -o s21_grep

clean:
	rm -rf s21_grep

rebuild:
		$(MAKE) clean
		$(MAKE) s21_grep