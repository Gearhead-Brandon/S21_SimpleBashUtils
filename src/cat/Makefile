CC=gcc 
CFLAGS=-c -Wall -Werror -Wextra

all: s21_cat

s21_cat: cat.o functions_cat.o
	$(CC) cat.o functions_cat.o -o s21_cat

cat.o: s21_cat.c header_cat.h
	$(CC) $(CFLAGS) s21_cat.c -o cat.o

functions_cat.o: functions_cat.c header_cat.h
	$(CC) $(CFLAGS) functions_cat.c -o functions_cat.o

clean:
	rm -rf *.o s21_cat