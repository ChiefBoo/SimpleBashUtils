TARGET = s21_grep
CC = gcc
CFLAGS = -Wall -Werror -Wextra -c

all: s21_grep

s21_grep: s21_grep.c s21_grep.h
	$(CC) $(CFLAGS) s21_grep.c 
	$(CC) s21_grep.o -o $(TARGET)

test: 	s21_grep
	sh test_grep.sh

clean:
	rm -rf *.o $(TARGET)

rebuild: clean all