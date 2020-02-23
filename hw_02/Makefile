all: main

main: bin/main.o bin/Board.o bin/BoardView.o
	g++ -Wall -Wextra bin/main.o bin/Board.o bin/BoardView.o -o main

bin/Board.o: src/Board.cpp include/Board.h
	g++ -c src/Board.cpp -I include -o bin/Board.o

bin/BoardView.o: src/BoardView.cpp include/Board.h include/BoardView.h
	g++ -c src/BoardView.cpp -I include -o bin/BoardView.o

bin/main.o: src/main.cpp include/Board.h include/BoardView.h
	g++ -c src/main.cpp -I include -o bin/main.o

board_test: bin/test.o bin/Test.o bin/BoardTest.o include/Test.h include/BoardTest.h bin/Board.o
	g++ bin/test.o bin/Test.o bin/BoardTest.o bin/Board.o -o board_test

bin/test.o: include/Test.h include/BoardTest.h
	g++ -c test/test.cpp -I include -o bin/test.o

bin/Test.o: include/Test.h test/Test.cpp
	g++ -c test/Test.cpp -I include -o bin/Test.o

bin/BoardTest.o: test/BoardTest.cpp include/Test.h include/Board.h include/BoardTest.h
	g++ -c test/BoardTest.cpp -I include -o bin/BoardTest.o

clean:
	rm bin/* main board_test
