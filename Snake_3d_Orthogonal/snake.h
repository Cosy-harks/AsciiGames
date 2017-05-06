#ifndef _SNAKE_H
#define _SNAKE_H
#include <vector>
#include <utility>

class Snake {
public:
	// Constructor for a snake
	Snake();
	// conversion constructor for a snake
	Snake(int x, int y, int z);
	// assignment operator assigning snake
	//to a new location in memory
	Snake& operator=(const Snake& s);

	// Update the direction
	void changeDirection(int d) { direction = d; }

	// The snake has eaten and needs to get bigger
	void grow();
	// update to the new positions of the pairs of snake
	void update();

	// Did the snake eat a wall
	bool outOfBounds();
	// Or did it eat itself
	bool didEatSelf();

	// i = index of snake body length; ".first"/".second.first"/".second.second" = 'x'/'y'/'z'
	int getXofPartI(int i) { return pos[i].first; }
	int getYofPartI(int i) { return pos[i].second.first; }
	int getZofPartI(int i) { return pos[i].second.second; }

	// returns the length of the snake
	int getLength() { return pos.size(); }
	// Returns the current direction
	char getDirection() { return direction; }

	// Returns true if the snake is alive
	bool isAlive() { return alive; }

	// Sets a new upperbound value. Lowerbound is already 0
	void setBounds(int size) { bounds = size; }
	// Returns the current bound
	int getBounds() { return bounds; }

	//true giveUp ==> false alive
	void gaveUp(bool b) { alive = !b; }

private:
	//holds each point for the body of the snake
	//pos.size() is the length of the snake
	std::vector<std::pair<int, std::pair<int, int>>> pos;

	/*std::vector is like a linked list.
	It is part of the STL (standard template library)
	A template is a class which takes in a data type as
	an argument when creating the class. This makes the
	template class dynamic and flexible for data types.
	for example, a vector can be created to hold ints, or
	floats, or doubles.
	I recommend that you look up vector on cplusplus.com
	to learn about this useful data structure.

	std::pair is a templated struct, which allows two different
	data members. These members can be the same or different
	data types. They are accessed using .first and .second
	*/

	// 'u' 'd' 'l' 'r' 'g' 's'
	char direction;
	// Basically the same as "playing"
	bool alive;
	// Number of spaces to stay within.
	int bounds;

};

#endif