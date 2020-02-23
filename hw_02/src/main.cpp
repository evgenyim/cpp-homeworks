#include <iostream>
#include <cstring>
#include "Board.h"
#include "BoardView.h"

int main(int argc, char** argv) {
	Board b;
	View v(b);
	if (argc > 1 && strcmp(argv[1], "silent") == 0) {
		v.set_silent();
	} else {
		v.showBoard();
	}
	while (!v.game_end()) {
		v.doGameCycle();
	}
	return 0;
}