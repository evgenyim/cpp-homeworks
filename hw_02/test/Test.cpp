#include <cstdio>
#include "Test.h"

Test::Test() {
	totalNum = 0;
	failedNum = 0;
}

void Test::showFinalResult() {
	if (failedNum == 0) {
		printf("All tests passed\n");
	} else {
		printf("Failed %d of %d tests\n", failedNum, totalNum);
	}
}

void Test::check(bool expr, const char *func, const char *filename, size_t lineNum) {
	totalNum++;
	if (!expr) {
		failedNum++;
		printf("Test failed: %s in %s:%zu\n", func, filename, lineNum);
	}
}