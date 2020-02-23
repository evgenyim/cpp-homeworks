#ifndef HW_02_BOARD_H
#define HW_02_BOARD_H

enum Game_Status {
	DRAW,
	X_WIN,
	O_WIN,
	IN_PROGRESS
};

class Board {
public:
	Board();
	~Board();
	void move(int x, int y, int sign);
	bool canMove(int x, int y, char sign) const;
	Game_Status isWin() const;
	char sign_to_char(int sign) const;
	char get(int x, int j) const;
	int get_size() const;
private:
	char **_board;
	int size, amount;
	int moves, last_x, last_y;
	char last_sign;
};

#endif
