#ifndef _SNAKEGAME_H
#define _SNAKEGAME_H

#include "Board.h"

class SnakeGame {
public:
	// initializes time between updates and
	//playing to false because the game hasn't started
	SnakeGame() { sleepTime = 500; playing = false; }
	// Enables the game
	void play();

	// reads each input from the keyboard
	void getUserInput();

private:
	// time between updates
	int sleepTime;
	// if true snake moves
	bool playing;
	// The SnakeGame needs a board to play on
	Board theBoard;
};

#endif