CC=gcc
CFLAGS=-c -Wall -Werror -Wextra

all: s21_grep

s21_grep: grep.o functions_grep.o
	$(CC) grep.o functions_grep.o -o s21_grep
 
grep.o: s21_grep.c s21_grep.h
	$(CC) $(CFLAGS) s21_grep.c -o grep.o

functions_grep.o: functions_grep.c s21_grep.h
	$(CC) $(CFLAGS) functions_grep.c -o functions_grep.o

clean:
	rm -rf *.o s21_grep