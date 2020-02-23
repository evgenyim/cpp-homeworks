#include <algorithm>
#include <cstdio>
#include "Board.h"

Board::Board() {
	moves = 0;
	size = 10, amount = 5;
	_board = new char*[size];
	for (int i = 0; i < size; i++) {
		_board[i] = new char[size];
		for (int j = 0; j < size; j++) {
			_board[i][j] = '.';
		}
	}
}

Board::~Board() {
	for (int i = 0; i < size; i++) {
		delete[] _board[i];
	}
	delete[] _board;
}

void Board::move(int x, int y, int sign) {
	char sign_ = sign_to_char(sign);
	if (sign == 1) {
		_board[x][y] = 'X';
	}
	if (sign == 0) {
		_board[x][y] = 'O';
	}
	moves++;
	last_x = x;
	last_y = y;
	last_sign = sign_;
}

bool Board::canMove(int x, int y, char sign) const {
	if (x < 0 || x >= size || y < 0 || y >= size) return false;
	return _board[x][y] == '.';
}

Game_Status Board::isWin() const {
	int cnt = 0;
	int x = last_x, y = last_y;
	char sign = last_sign;
	for (int i = 0; i < size; i++) {
		if (_board[x][i] == sign) {
			cnt++;
		} else {
			cnt = 0;
		}
		if (cnt == amount) {
			if (sign == 'X') {
				return X_WIN;
			}
			if (sign == 'O') {
				return O_WIN;
			}
		}
	}
	cnt = 0;
	for (int i = 0; i < size; i++) {
		if (_board[i][y] == sign) {
			cnt++;
 		} else {
			cnt = 0;
		}
		if (cnt == amount) {
			if (sign == 'X') {
			return X_WIN;
			}
			if (sign == 'O') {
				return O_WIN;
			}
		}
	}
	cnt = 0;
	int a = x - std::min(x, y), b = y - std::min(x, y);
	while (a < size && b < size) {
		if (_board[a][b] == sign) {
			cnt++;
		} else {
			cnt = 0;
		}
		if (cnt == amount) {
			if (sign == 'X') {
			return X_WIN;
			}
			if (sign == 'O') {
				return O_WIN;
 			}
		}
		a++, b++;
	}
	cnt = 0;
	a = x - std::min(x, 9 - y), b = y + std::min(x, 9 - y);
	while (a < size && b >= 0) {
		if (_board[a][b] == sign) {
			cnt++;
		} else {
			cnt = 0;
		}
		if (cnt == amount) {
			if (sign == 'X') {
 				return X_WIN;
			}
			if (sign == 'O') {
				return O_WIN;
			}
		}
		a++, b--;
	}
	if (moves == size * size) {
		return DRAW;
	}
	return IN_PROGRESS;
}

char Board::sign_to_char(int sign) const {
	if (sign == 1) {
		return 'X';
	}
	if (sign == 0) {
		return 'O';
	}
	return '.';
}

char Board::get(int x, int y) const {
	return _board[x][y];
}

int Board::get_size() const {
	return size;
}
