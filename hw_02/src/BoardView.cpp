#include <cstdio>
#include "BoardView.h"

View::View(Board &board) {
	b = &board;
	cur_player = 0;
	game_over = false, silent = false;
}

void View::showBoard() const {
	printf("\n");
	for (int i = 0; i < b->get_size(); i++) {
		for (int j = 0; j < b->get_size(); j++) {
			printf("%c", b->get(i, j));
		}
		printf("\n");
	}
}

void View::doGameCycle() {
	char sign = b->sign_to_char(cur_player);
	printf("%c move: ", sign);
	int x, y;
	scanf("%d %d", &x, &y);
	while (!b->canMove(x, y, sign)) {
		if (x == -1 && y == -1) {
			game_over = true;
			return;
		}
		printf("Bad move!\n");
		printf("%c move: ", sign);
		scanf("%d %d", &x, &y);
	}
	b->move(x, y, cur_player);
	if (!silent) {
		showBoard();
	}
	Game_Status win = b->isWin();
	if (win != IN_PROGRESS && silent) {
		showBoard();
	}
	if (win == O_WIN) {
		printf("O wins!\n");
		game_over = true;
	} else if (win == X_WIN) {
		printf("X wins!\n");
		game_over = true;
	} else if (win == DRAW) {
		printf("Draw.\n");
		game_over = true;
	}
	cur_player = (cur_player + 1) % 2;
}

void View::set_silent() {
	silent = true;
}

bool View::game_end() const {
	return game_over;
}