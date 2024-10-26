FLAGS=-Wall -Wextra
OUTPUT=passgen.o

main:
	gcc ${FLAGS} main.c -o ${OUTPUT}

clear:
	rm -rf *.o
