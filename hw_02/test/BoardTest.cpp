#include "BoardTest.h"
#include "Board.h"
#define DO_CHECK(EXPR) check(EXPR, __FUNCTION__, __FILE__, __LINE__)

void BoardTest::testIsWin1() {
	Board b;
	b.move(0, 0, 1);
	b.move(0, 1, 1);
	b.move(1, 0, 1);
	b.move(4, 5, 0);
	b.move(5, 5, 0);
	DO_CHECK(b.isWin() == IN_PROGRESS);
}

void BoardTest::testIsWin2() {
	Board b;
	for (int i = 0; i < 5; i++) {
		b.move(i, 0, 1);
	}
	DO_CHECK(b.isWin() == X_WIN);
}

void BoardTest::testIsWin3() {
	Board b;
	for (int i = 2; i < 7; i++) {
		b.move(5, i, 0);
	}
	DO_CHECK(b.isWin() == O_WIN);
}

void BoardTest::testIsWin4() {
	Board b;
	for (int i = 1; i < 6; i++) {
		b.move(i, i + 1, 1);
	}
	DO_CHECK(b.isWin() == X_WIN);
}

void BoardTest::testIsWin5() {
	Board b;
	for (int i = 3; i < 8; i++) {
		b.move(i, 9 - i, 1);
	}
	DO_CHECK(b.isWin() == X_WIN);
}

void  BoardTest::testIsWin6() {
	Board b;
	for (int i = 0; i < 10; i+= 4) {
		for (int j = 0; j < 10; j+= 2) {
			b.move(i, j, 1);
			b.move(i + 1, j, 1);
			b.move(i, j + 1, 0);
			b.move(i + 1, j + 1, 0);
		}
	}
	for (int i = 2; i < 10; i+= 4) {
		for (int j = 0; j < 10; j+= 2) {
			b.move(i, j, 0);
			b.move(i + 1, j, 0);
			b.move(i, j + 1, 1);
			b.move(i + 1, j + 1, 1);
		}
	}
	DO_CHECK(b.isWin() == DRAW);
}

void BoardTest::testMove1() {
	Board b;
	b.move(0, 0, 1);
	DO_CHECK(!b.canMove(0, 0, 0));
}

void BoardTest::testMove2() {
	Board b;
	b.move(0, 0, 1);
	DO_CHECK(b.canMove(1, 1, 1));
}

void BoardTest::testMove3() {
	Board b;
	b.move(0, 0, 1);
	DO_CHECK(!b.canMove(10, 10, 1));
}

void BoardTest::testGet1() {
	Board b;
	b.move(7, 8, 1);
	DO_CHECK(b.get(7, 8) == 'X');
}

void BoardTest::testGet2() {
	Board b;
	b.move(9, 9, 0);
	DO_CHECK(b.get(9, 9) == 'O');
}

void BoardTest::testGet3() {
	Board b;
	b.move(9, 5, 0);
	DO_CHECK(b.get(9, 6) == '.');
}

void BoardTest::testSignToChar1() {
	Board b;
	DO_CHECK(b.sign_to_char(1) == 'X');
}

void BoardTest::testSignToChar2() {
	Board b;
	DO_CHECK(b.sign_to_char(0) == 'O');
}

void BoardTest::testSignToChar3() {
	Board b;
	DO_CHECK(b.sign_to_char(-1) == '.');
}

void BoardTest::runAllTests() {
	testIsWin1();
	testIsWin2();
	testIsWin3();
	testIsWin4();
	testIsWin5();
	testIsWin6();
	testMove1();
	testMove2();
	testMove3();
	testGet1();
	testGet2();
	testGet3();
	testSignToChar1();
	testSignToChar2();
	testSignToChar3();
}