#ifndef _BOARD_H
#define _BOARD_H

#include "Snake.h"
#include <string>

using namespace std;

class Board {
public:
	// Constructs an object of type board
	Board();
	// Updates placement of objects on the board
	void update();
	// update placement of the fruit
	void placeFruit();
	// Returns integer between 1 and 16; just w/in the boarders.
	int randomPoint() { return 1 + (rand() % (size - 2)); }
	// Clears and reprints the board
	void display();
	// prints a single row to the console
	void displayLine(int row, string orientation);
	// Gets input from function used to determine direction
	void parseInput(char c);
	// boolean true if playing.
	bool isPlaying() { return playing; }

private:
	//why is this a const static int and not an int?

	// A const static int won't change and is only made
	//once to be used by all instances of class board.
	//w/out const we wouldn't be able to initialize it here
	//w/out static we wouldn't be able to initialize other 
	const static int size = 18;

	// assign the size of the 3D board
	string tiles[size][size][size];
	string angles;

	// The board holds the snake's positions
	Snake theSnake;

	//how can we use std::pair in this header?
	//why don't we have to include <utility> for it?

	// We can use std::pair because we include the <utility>
	//header in the included "snake.h" header.
	std::pair<int, std::pair<int, int> > fruit;

	// 
	bool playing;
};

#endif