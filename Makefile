CC          := clang -std=c99
CFLAGS      := -Wall -Wextra -Werror

day_01 : src/day_01.c
	$(CC) src/day_01.c -o build/day_01
	build/day_01 < ~/input/01.txt

.PHONY : clean

clean :
	rm -f build/*

test: 
