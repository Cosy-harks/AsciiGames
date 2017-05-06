#include "Board.h"
#include <iostream>
#include <ctime>
#include <string>

using namespace std;
/*
										  - - |- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
										| \	  |																/ |
										| _\ _/															   /  |
										|   \  \ 												          /	  |
										|	 \  \														 /	  |
										|	  \	 \														/	  |
										|	   \  \													   /	  |
										|		\  \												  /		  |
										|		 \  \												 /		  |
										|		  \  \												/		  |
										|		   \ \											   /		  |
										|			\ \											  /			  |
										|			 \ \										 /			  |
										|			  \ \										/			  |
18 === 0-9, A-H. DEFAULT BOARD			|			   \ \									   /			  |
playable area = [1 <-> 16]				|				\ \									  /				  |
  0 1 2 3 4 5 6 7 8 9 A B C D E F G H	|  X-axis		 \0 1 2 3 4 5 6 7 8 9 A B C D E F G H/   Z-axis		  |
0   - - - - - - - - - - - - - - - -		|				0 X - - - - - - - - - - - - - - - -  				  |
1 |  \                           /  |	|				1 |									|				  |
2 |   \                         /   |	|				2 |									|				  |
3 |    \                       /    |	|				3 |									|				  |
4 |     \                     /     |	|				4 |									|				  |
5 |      \___________________/      |	|				5 |									|				  |
6 |      |                   |      |	|				6 |									|				  |
7 |      |                   |      |	|				7 |									|				  |
8 |      |                   |      |	|				8 |									|				  |
9 |      |                   |      |	|				9 |									|				  |
A |      |___________________|	    |	|				A |									|				  |
B |      /                   \      |	|				B |									|				  |
C |     /                     \     |	|				C |									|				  |
D |    /                       \    |	|				D |									|				  |
E |   /                         \   |	|				E |									|				  |
F |  /                           \  |	|				F |									|				  |
G | /                             \ |	|				G |									|				  |
H   - - - - - - - - - - - - - - - -		|				H  - - - - - - - - - - - - - - - - - 				  |
										|				  /									\				  |
Y										|			Y    /									 \				  |
|										|			|   /									  \				  |
a										|			a  /									   \			  |
x										|			x /											\			  |
i										|			i/											 \			  |
s										|		    s											  \			  |
										|		   /											   \		  |
0 1 2 3 4 5 6 7 8 9 A B C D E F G H	  X-axis	  /													\		  |
0   - - - - - - - - - - - - - - - -		|		 /													 \		  |
1 |                                 |	|	    /													  \		  |
2 |                                 |	|	   /													   \	  |
3 |                                 |	|	  /															\	  |
4 |                                 |	|	 /															 \	  |
5 |                                 |	|   /															  \	  |
6 |                                 |	|  /															   \  |
7 |                                 |	| /																	\ |
8 |                                 |	  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
9 |                                 |
A |                                 |
B |                                 |
C |                                 |
D |                                 |
E |                                 |
F |                                 |
G |                                 |
H   - - - - - - - - - - - - - - - -

Z
|
a
x
i
s
*/

// Playing field
Board::Board()
{
	// makes a seed to randomize start position
	//and fruit locations
	srand(time(NULL));

	// x increment till size
	for (int x = 0; x < size; x++)
	{
		// y increment till size for every x value
		for (int y = 0; y < size; y++)
		{
			for (int z = 0; z < size; z++) {
				// tiles 
				tiles[x][y][z] = "  ";
			}
		}
	}

	// assign boarder
	for (int i = 0; i < size; i++)
	{
		//X incr
		//top forward edge
		tiles[i][0][0] = " -";
		//top backward edge
		tiles[i][size - 1][0] = "- ";
		//lower forward edge
		tiles[i][0][size - 1] = "- ";
		//lower backward edge
		tiles[i][size - 1][size - 1] = " -";

		//Y incr
		//top left edge
		tiles[0][i][0] = " | ";
		//top right edge
		tiles[size - 1][i][0] = " | ";
		//bottom left edge
		tiles[0][i][size - 1] = "| ";
		//bottom right edge
		tiles[size - 1][i][size - 1] = " |";

		//Z incr
		//forward left column
		tiles[0][0][i] = " \\ ";
		//forward right column
		tiles[size - 1][0][i] = " / ";
		//backward left column
		tiles[0][size - 1][i] = " / ";
		//backward right column
		tiles[size - 1][size - 1][i] = " \\ ";
	}
	//tiles[0][size - 1][0] = "- ";// asthetics

	// Assign snake head position and makes sure the snake
	//is w/in the board.
	theSnake = Snake(randomPoint(), randomPoint(), randomPoint());

	// idkw.
	theSnake.setBounds(size - 2);

	// Picks a spot for the fruit w/in
	//bounds and not on thesnake
	placeFruit();

	playing = true;
}

// The board gets new locations for content
void Board::update()
{
	// the snake moves this function records it
	theSnake.update();

	// checks if the snake is alive
	playing = theSnake.isAlive();

	// checks if the snake has eaten a friut
	if (theSnake.getXofPartI(0) == fruit.first && theSnake.getYofPartI(0) == fruit.second.first && theSnake.getZofPartI(0) == fruit.second.second)
	{
		// the snake grows
		theSnake.grow();
		// a new fruit location needs to be determined
		placeFruit();
	}
}

// picks a spot for the fruit
void Board::placeFruit()
{
	// .first is x-coordinate, it gets a number between 1 and 16
	fruit.first = randomPoint();
	// .second is y-coordinate, it gets a number between 1 and 16
	fruit.second.first = randomPoint();
	fruit.second.second = randomPoint();

	// loops the snakes length
	for (int i = 0; i < theSnake.getLength(); i++)
	{
		// checks for fruit being on/under snake
		if (theSnake.getXofPartI(i) == fruit.first && theSnake.getYofPartI(i) == fruit.second.first && theSnake.getZofPartI(i) == fruit.second.second)
		{
			// Picks new spot for fruit, because it was found on the snake
			fruit.first = randomPoint();
			fruit.second.first = randomPoint();
			fruit.second.second = randomPoint();
			// just in case the fruit landed on the snake again
			i = 0;
		}
	}
}


void Board::display()
{
	// place fruit in its determined place
	tiles[fruit.first][fruit.second.first][fruit.second.second] = " *";

	// does not write over head
	if (theSnake.getLength() == 3)
	{
		for (int i = 1; i < theSnake.getLength(); i++)
		{
			// Places snake body parts onto the board
			//in each of its positions
			tiles[theSnake.getXofPartI(i)][theSnake.getYofPartI(i)][size-1] = " %";
			tiles[theSnake.getXofPartI(i)][theSnake.getYofPartI(i)][theSnake.getZofPartI(i)] = " @";
		}
	}
	else {
		for (int i = theSnake.getLength() - 1; tiles[theSnake.getXofPartI(i)][theSnake.getYofPartI(i)][theSnake.getZofPartI(i)] != " @" && i != 0; i--)
		{
			// Places snake body parts onto the board
			//in each of its positions
			tiles[theSnake.getXofPartI(i)][theSnake.getYofPartI(i)][size-1] = " %";
			tiles[theSnake.getXofPartI(i)][theSnake.getYofPartI(i)][theSnake.getZofPartI(i)] = " @";
		}
		// places snake body part where its head was in the previous update
		tiles[theSnake.getXofPartI(1)][theSnake.getYofPartI(1)][size-1] = " %";
		tiles[theSnake.getXofPartI(1)][theSnake.getYofPartI(1)][theSnake.getZofPartI(1)] = " @";
	}

	// Print basic instructions
	//angles = "\nq: to quit\n8: up\t5: down\t\t\t\t\t\t8: up\t5: down\n4: left\t6: right\t\t\t\t\t9: left\t3:right\n9: deeper\t3: surfacing\t\t\t\t4: deeper\t6: surfacing\n";

	// print the board to console
	displayLine(0, "xy");

	// clears the console of printed information
	system("cls");
	cout << angles;
	angles.clear();
	// removes snake from board completely so we don't have to keep track
	//of conditions.
	//for (int i = 0; i < theSnake.getLength(); i++)
	//{

	// Only the last snake body part will need to be taken off
	tiles[theSnake.getXofPartI(theSnake.getLength() - 1)][theSnake.getYofPartI(theSnake.getLength() - 1)][size-1] = "  ";
	tiles[theSnake.getXofPartI(theSnake.getLength() - 1)][theSnake.getYofPartI(theSnake.getLength() - 1)][theSnake.getZofPartI(theSnake.getLength() - 1)] = "  ";
	//}
}

void Board::displayLine(int row, string orientation) {

	switch (theSnake.getDirection())
	{
	case 'u':// up
		tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " ^";
		break;
	case 'd':// down
		tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " v";
		break;
	case 'l':// left
		tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " <";
		break;
	case 'r':// right
		tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " >";
		break;
	case 's':// surfacing
		tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " 0";
		break;
	case'g':// deepening
		tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " a";
		break;
	default:
		break;
	}

	// Idea: color the X,Y,Z borders where the snake is and also the fruit

	string square[size * 2][size * 2] = { "  " };
	for (int I = 0; I < size * size * 4; I++) { square[int(I / 36)][I % 36] = "  "; }

	//creates representation for board
	for (float I = 1.7; I >= 0; I -= .1) {
		for (int xI = 0; xI < size; xI++) {
			for (int yI = 0; yI < size; yI++) {
				if (tiles[xI][yI][int(10 * I)] != "  ") {
					if (xI < 6 && yI < 6) {
						square[8 + xI - int(10 * (abs(I - 1.7) / 2))][8 + yI - int(10 * (abs(I - 1.7) / 2))] = tiles[xI][yI][int(10 * I)];
					}
					else if (xI < 12 && yI < 6) {
						square[8 + xI][8 + yI - int(10 * (abs(I - 1.7) / 2))] = tiles[xI][yI][int(10 * I)];
					}
					else if (xI < size && yI == 0 && I != 0) {
						square[8 + xI + int(10 * (abs(I - 1.7) / 2))][8 + yI - int(10 * (abs(I - 1.7) / 2))] = tiles[xI][yI][int(10 * I)];
					}
					else if (xI < size && yI == 0) {
						square[8 + xI + int(10 * (abs(I - 1.7) / 2))][8 + yI - int(10 * (abs(I - 1.7) / 2))] = tiles[xI][yI][int(10 * I)];
					}
					else if (xI < size && yI < 6) {
						square[8 + xI + int(10 * (abs(I - 1.7) / 2))][8 + yI + int(10 * (abs(I - 1.7) / 2))] = tiles[xI][yI][int(10 * I)];
					}
					else if (xI < 6 && yI < 12) {
						square[8 + xI - int(10 * (abs(I - 1.7) / 2))][8 + yI] = tiles[xI][yI][int(10 * I)];
					}
					else if (xI < 12 && yI < 12) {
						square[8 + xI][8 + yI] = tiles[xI][yI][int(10 * I)];
					}
					else if (xI < size && yI < 12) {
						square[8 + xI + int(10 * (abs(I - 1.7) / 2))][8 + yI] = tiles[xI][yI][int(10 * I)];
					}
					else if (xI < 6 && yI < size) {
						square[8 + xI - int(10 * (abs(I - 1.7) / 2))][8 + yI + int(10 * (abs(I - 1.7) / 2))] = tiles[xI][yI][int(10 * I)];
					}
					else if (xI < 12 && yI < size) {
						square[8 + xI][8 + yI + int(10 * (abs(I - 1.7) / 2))] = tiles[xI][yI][int(10 * I)];
					}
					else if (xI < size && yI < size) {
						square[8 + xI + int(10 * (abs(I - 1.7) / 2))][8 + yI + int(10 * (abs(I - 1.7) / 2))] = tiles[xI][yI][int(10 * I)];
					}
				}
			}
		}
	}




	if (orientation == "xy") {
		// determines direction of snake head and
		//puts in char specified for each direction
		switch (theSnake.getDirection())
		{
		case 'u':// up
			tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " ^";
			break;
		case 'd':// down
			tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " v";
			break;
		case 'l':// left
			tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " <";
			break;
		case 'r':// right
			tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " >";
			break;
		case 's':// surfacing
			tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " 0";
			break;
		case'g':// deepening
			tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " a";
			break;
		default:
			break;
		}
		/*for (int i = 0; i < size-1; i++) {
			for (int x = 0, y = i, z = 0; y >= 0; y--) {
				for (z = 0; z < i; z++) {
					for (x = 0; x < size; x++) {
						if (tiles[x][y][z] != "  ") {
							angles.append(tiles[x][y][z]);
						}
					}
					angles.append("  ");
					
				}
				angles.append("\n");
				
			}
		}*//*


		for (int height = 0; height < size * 3; height++) {
			if (height < size) {
				for (int y = 0, l = 0; y <= 0; y++, l++) {
					for (int x = 0; x < size ; x++) {
						angles.append(tiles[x][y][0]);
					}
					angles.append("\n");
				}

			}
		}*/


	/*	for (int x = 0; x < size; x++) {
			angles.append(tiles[x][0][0]);
		}
		angles.append("\n");
//		X[0, 18], Y[0], Z[0]

		angles.append(tiles[0][1][0]);
//		X[0], Y[1], Z[0]

		for (int x = 0; x < size; x++) {
			angles.append(tiles[x][0][1]);
		}
		angles.append(tiles[size - 1][1][0]);
		angles.append("\n");
//		X[1, 17], Y[0], Z[1]

		for (int x = 0; x <= 1; x++) {
			angles.append(tiles[x][2][0]);
		}
//		X[0, 1], Y[2], Z[0]

		for (int x = 0; x < size; x++) {
			angles.append(tiles[x][0][2]);
		}
//		X[2, 16], Y[0], Z[2]

		for (int x = size - 2; x < size; x++) {
			angles.append(tiles[x][2][0]);
		}
		angles.append("\n");
//		X[17], Y[2], Z[0]

		for (int x = 0; x <= 2; x++) {
			angles.append(tiles[x][3][0]);
		}
//		X[0, 2], Y[3], Z[0]

		for (int x = 0; x < size; x++) {
			angles.append(tiles[x][0][3]);
		}
//		X[3, 15], Y[0], Z[3]

		for (int x = size - 3; x < size; x++) {
			angles.append(tiles[x][3][0]);
		}
		angles.append("\n");
//		X[16, 17], Y[3], Z[0]

		for (int x = 0; x <= 4; x++) {
			angles.append(tiles[x][4][0]);
		}
//		X[0, 4], Y[4], Z[0]

		for (int x = 0; x < size - 4; x++) {
			angles.append(tiles[x][0][4]);
		}
//		X[5, 14], Y[0], Z[4]

		for (int x = 15; x < size; x++) {
			angles.append(tiles[x][4][0]);
		}
		angles.append("\n");
//		X[15, 17], Y[4], Z[0]


//		X[0, 5], Y[5], Z[0]
//		X[6, 13], Y[0], Z[5]
//		X[14, 18], Y[5], Z[0]
//		X[0, 6], Y[6], Z[0]
//		X[7, 12], Y[0], Z[6]
//		X[13, 18], Y[6], Z[0]
//		X[0, 7], Y[7], Z[0]
//		X[8, 11], Y[0], Z[7]
//		X[12, 18], Y[7], Z[0]
//		X[0, 8], Y[8], Z[0]
//		X[9, 10], Y[0], Z[5]
//		X[11, 18], Y[8], Z[0]
//		X[0, 9], Y[9], Z[0]
//		X[10, 9], Y[0], Z[9]
//		X[10, 18], Y[9], Z[0]*/

	}
	if (orientation == "zy") {
		// determines direction of snake head and
		//puts in char specified for each direction
		switch (theSnake.getDirection())
		{
		case 'u':// up
			tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " ^";
			break;
		case 'd':// down
			tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " v";
			break;
		case 'l':// left
			tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " a";
			break;
		case 'r':// right
			tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " 0";
			break;
		case 's':// surfacing
			tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " <";
			break;
		case'g':// deepening
			tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " >";
			break;
		default:
			break;
		}
		for (int x = 0, z = 0; z < size; z++) {
			for (x = size - 1; x > 1; x--) {
				if (tiles[x][row][z] != "  ") {
					break;
				}
			}
			angles.append(tiles[x][row][z]);
		}
	}
	else if (orientation == "xz") {
		// determines direction of snake head and
		//puts in char specified for each direction
		switch (theSnake.getDirection())
		{
		case 'u':// up
			tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " a";
			break;
		case 'd':// down
			tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " 0";
			break;
		case 'l':// left
			tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " <";
			break;
		case 'r':// right
			tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " >";
			break;
		case 's':// surfacing
			tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " ^";
			break;
		case'g':// deepening
			tiles[theSnake.getXofPartI(0)][theSnake.getYofPartI(0)][theSnake.getZofPartI(0)] = " v";
			break;
		default:
			break;
		}
		/*for (int x = 0, y = 0; x < size; x++) {
			for (y = size - 1; y > 0; y--) {
				if (tiles[x][y][row] != "  ") {
					break;
				}
			}
			angles.append(tiles[x][y][row]);*/
	}
	
	angles.clear();
	for (int yI = 0; yI < size * 2; yI++) {
		for (int xI = 0; xI < size * 2; xI++) {
			angles.append(square[xI][yI]);
		}
		angles.append("\n");
	}
}

void Board::parseInput(char c)
{
	// input for changing direction
	switch (c)
	{
	case 'q':// quit
			 // No longer playing
		playing = false;
		// theSnake.gaveUp == true makes theSnake.alive == false
		theSnake.gaveUp(!playing);
		cout << "\nEXITING\n";
		break;
	case '4':// left
		theSnake.changeDirection('l');
		break;
	case '8':// up
		theSnake.changeDirection('u');
		break;
	case '6':// right
		theSnake.changeDirection('r');
		break;
	case '5':// down
		theSnake.changeDirection('d');
		break;
	case '3':// depth
		theSnake.changeDirection('g');
		break;
	case '9':// depth
		theSnake.changeDirection('s');
		break;
	default: // characters other than "dawqs"
		break;
	}
}