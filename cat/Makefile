CC = gcc
CFLAGS = -Wall -Wextra -Werror 

all: clean s21_cat

s21_cat: cat.c cat.h
	$(CC) $(CFLAGS) cat.c -o s21_cat

clean:
	rm -rf s21_cat

rebuild:
		$(MAKE) clean
		$(MAKE) s21_cat