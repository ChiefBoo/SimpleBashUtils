TARGET = s21_cat
CC = gcc
CFLAGS = -Wall -Werror -Wextra -c

all: s21_cat

s21_cat: s21_cat.c s21_cat.h
	$(CC) $(CFLAGS) s21_cat.c 
	$(CC) s21_cat.o -o $(TARGET)

test: 	s21_cat
	sh test_cat.sh

clean:
	rm -rf *.o $(TARGET)

rebuild: clean all