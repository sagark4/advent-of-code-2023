CC          := clang -std=c99 -g 
CFLAGS      := -Wall -Wextra -Werror

build/day_04 : build/day_04.o
	$(CC) build/day_04.o -o build/day_04
	build/day_04 < ~/input/04.txt

build/day_04.o : src/day_04.c
	$(CC) -c src/day_04.c -o build/day_04.o

build/day_03 : build/day_03.o
	$(CC) build/day_03.o -o build/day_03
	build/day_03 < ~/input/03.txt

build/day_03.o : src/day_03.c
	$(CC) -c src/day_03.c -o build/day_03.o

build/day_02 : build/day_02.o build/psed.o
	$(CC) build/day_02.o build/psed.o -o build/day_02
	build/day_02 < ~/input/02.txt

build/day_02.o : src/day_02.c src/include/psed.h
	$(CC) -c src/day_02.c -o build/day_02.o

build/psed.o : src/psed.c src/include/psed.h
	$(CC) -c src/psed.c -o build/psed.o

build/day_01 : src/day_01.c
	$(CC) src/day_01.c -o build/day_01
	build/day_01 < ~/input/01.txt

.PHONY : clean

clean :
	rm -f build/*

test: 
