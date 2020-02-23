#ifndef HW_02_BOARDVIEW_H
#define HW_02_BOARDVIEW_H

#include "Board.h"

class View {
public:
	View(Board &board);
	void showBoard() const;
	void doGameCycle();
	void set_silent();
	bool game_end() const;
private:
	Board *b;
	int cur_player;
	bool game_over, silent;
};

#endif
