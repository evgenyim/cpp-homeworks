main: bin/main.o bin/bmp.o
	gcc -g -std=c99 -Wall -Werror bin/main.o bin/bmp.o -o main
bin/main.o: src/main.c include/bmp.h
	gcc -c src/main.c -I include -o bin/main.o
bin/bmp.o: src/bmp.c include/bmp.h
	gcc -c src/bmp.c -I include -o bin/bmp.o
clean:
	rm bin/* main
