#ifndef HW_02_BOARDTEST_H
#define HW_02_BOARDTEST_H

#include "Test.h"

class BoardTest: public Test {
public:
	void testIsWin1();
	void testIsWin2();
	void testIsWin3();
	void testIsWin4();
	void testIsWin5();
	void testIsWin6();
	void testMove1();
	void testMove2();
	void testMove3();
	void testGet1();
	void testGet2();
	void testGet3();
	void testSignToChar1();
	void testSignToChar2();
	void testSignToChar3();
	void runAllTests();
};

#endif