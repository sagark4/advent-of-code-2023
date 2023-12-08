CC          := clang -std=c99 -gdwarf-4 
CFLAGS      := -Wall -Wextra -Werror

build/day_07 : build/day_07.o
	$(CC) build/day_07.o -o build/day_07

build/day_07.o : src/day_07.c
	$(CC) -c src/day_07.c -o build/day_07.o

build/day_06 : build/day_06.o
	$(CC) build/day_06.o -o build/day_06

build/day_06.o : src/day_06.c
	$(CC) -c src/day_06.c -o build/day_06.o

build/day_05 : build/day_05.o
	$(CC) build/day_05.o -o build/day_05

build/day_05.o : src/day_05.c
	$(CC) -c src/day_05.c -o build/day_05.o

build/day_04 : build/day_04.o
	$(CC) build/day_04.o -o build/day_04

build/day_04.o : src/day_04.c
	$(CC) -c src/day_04.c -o build/day_04.o

build/day_03 : build/day_03.o
	$(CC) build/day_03.o -o build/day_03

build/day_03.o : src/day_03.c
	$(CC) -c src/day_03.c -o build/day_03.o

build/day_02 : build/day_02.o build/psed.o
	$(CC) build/day_02.o build/psed.o -o build/day_02

build/day_02.o : src/day_02.c src/include/psed.h
	$(CC) -c src/day_02.c -o build/day_02.o

build/psed.o : src/psed.c src/include/psed.h
	$(CC) -c src/psed.c -o build/psed.o

build/day_01 : src/day_01.c
	$(CC) src/day_01.c -o build/day_01

all : build/day_01 build/day_02 build/day_03 build/day_04 build/day_05 build/day_06 build/day_07 
run_all : all
	build/day_01 < ~/input/01.txt
	build/day_02 < ~/input/02.txt
	build/day_03 < ~/input/03.txt
	build/day_04 < ~/input/04.txt
	build/day_05 < ~/input/05.txt
	build/day_06 < ~/input/06.txt
	build/day_07 < ~/input/07.txt
	python src/day_08.py < ~/input/08.txt

valgrind_all : all
	valgrind build/day_01 < ~/input/01.txt
	valgrind build/day_02 < ~/input/02.txt
	valgrind build/day_03 < ~/input/03.txt
	valgrind build/day_04 < ~/input/04.txt
	valgrind build/day_05 < ~/input/05.txt
	valgrind build/day_06 < ~/input/06.txt
	valgrind build/day_07 < ~/input/07.txt

.PHONY : clean

clean :
	rm -f build/*

test: 
