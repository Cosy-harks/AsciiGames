#include "Snake.h"
#include <iostream>

using namespace std;

// Constructs a snake object
Snake::Snake()
{
	// checks that the snake is w/in the board
	bounds = 16;

	// starting direction is down
	direction = 'd';

	// starting position is saved
	for (int i = 0; i < 3; i++)
	{
		//use the {} to construct a pair within the push_back method
		pos.push_back({ 8, {8 - i, 8 - i } });
	}
	// It's ALIVE!
	alive = true;
}

// creates a snake via converting two integers into pairs to be used by "pos"
Snake::Snake(int x, int y, int z)
{
	// keep snake w/in the board
	bounds = 16;

	// Check snake position move if it's out of bounds
	if (x < 1) {
		x = 1;
	}
	else if (x > 16) {
		x = 16;
	}
	if (y < 3) {
		y = 3;
	}
	else if (y > 16) {
		y = 14;
	}
	if (z < 3) {
		z = 3;
	}
	else if (z > 16) {
		z = 14;
	}

	// initial direction is down
	direction = 'd';

	// assign snake location
	for (int i = 0; i < 3; i++)
	{
		// attach the coordinate pair to the snake as a position
		pos.push_back({ x, { y - i, z } });
	}

	// begining of the game the snake lives
	alive = true;
}

// assignment. Snake's data gets moved to another snake variable
Snake& Snake::operator=(const Snake& s)
{
	// assigning bounds of "s" to bounds of "this"
	this->bounds = s.bounds;

	// assign direction to "this" snake
	this->direction = s.direction;

	// deletes the pairs from "pos" so the snake isn't just really long. 
	this->pos.clear();

	// loop the length of the snake "s"
	for (int i = 0; i < s.pos.size(); i++)
	{
		// assigns the pairs of "s" to "this"
		this->pos.push_back(s.pos[i]);
	}

	// bool for determining if the snake is alive
	this->alive = s.alive;

	// the assigned snake is returned
	return *this;
}

void Snake::grow()
{
	// adds a body position at the end of the snake
	pos.push_back(pos[pos.size() - 1]);
}

void Snake::update()
{
	// moves each snake position forward one so the snake can move
	for (int i = pos.size() - 1; i > 0; i--)
	{
		// gets the pair's position ahead of it
		pos[i] = pos[i - 1];
	}
	// This makes for an interesting game
	//pos[pos.size() - 1].first = pos[0].first;
	//pos[pos.size() - 1].second = pos[0].second;

	// (de/in)crement head position based on the direction
	switch (direction)
	{
	case 'g':// deepening
		// z position incremented
		pos[0].second.second++;
		break;
	case 's':// shallowing
		// z position decrementing
		pos[0].second.second--;
		break;
	case 'u':// up
			 // y position decremented
		pos[0].second.first--;
		break;
	case 'd':// down
			 // y position incremented
		pos[0].second.first++;
		break;
	case 'l':// left
			 // x position decremented
		pos[0].first--;
		break;
	case 'r':// right
			 // x position incremented
		pos[0].first++;
		break;
	default:
		break;
	}

	// check for hitting a wall
	outOfBounds();
	// check for eating itself
	didEatSelf();
}

// determines if the snake ate a wall
bool Snake::outOfBounds()
{
	// Checks to see if snake head ate the left or right wall
	//it uses pos[0] because that's where the head is and the
	//body alway follows the path of the head so it won't go out of bounds
	//before the head.
	if (pos[0].first < 1 || pos[0].first > bounds)
	{
		// Condition met the snake ate a wall and ruined his
		//digestion, killing himself
		alive = false;
		cout << "\n\nYOU WENT OUT OF BOUNDS\n\n";
	}
	// Checks to see if snake head ate the top or bottom wall.
	//"..."
	else if (pos[0].second.first < 1 || pos[0].second.first > bounds)
	{
		// Condition met the snake ate a wall and ruined his
		//digestion, killing himself
		alive = false;
		cout << "\n\nYOU WENT OUT OF BOUNDS\n\n";
	}
	// Checks to see if snake head ate the ground or the ceiling.
	//"..."
	else if (pos[0].second.second < 1 || pos[0].second.second > bounds)
	{
		// Condition met the snake ate a wall and ruined his
		//digestion, killing himself
		alive = false;
		cout << "\n\nYOU WENT OUT OF BOUNDS\n\n";
	}

	// returns boolean determining if the snake is dead
	return alive;
}

// Determines if the snake ate itself
bool Snake::didEatSelf()
{
	// Loop for the size of the snake if it's alive
	for (int i = 1; i < pos.size() && alive; i++)
	{
		// compares the head position to each body sections position
		if (pos[0] == pos[i])
		{
			// Condition is met the snake ate itself resulting in death
			alive = false;
			// Prints the words in "..." to the display
			cout << "\n\nYOU ATE YOURSELF!\n\tYOU CANNIBAL!\n\n";
			// breaks from loop
			break;
		}
	}
	// returns boolean determining if the snake is dead
	return alive;
}