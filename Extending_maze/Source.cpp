#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

using namespace std;

#define ROW 21
#define COL 79

int wall[ROW][COL] = { 0 };
void creatWalls(int, int);
void theWalls(int, int);
void move(int, int);
void endGame();
void shift(int);
void case0(int, int, int);
void BuildEnd(int);

// project
void main()
{
	srand((unsigned)time(NULL));
	printf("Use the characters 'W A S D' to move your character! Or 'spacebar' to end the game.\n");
	printf("Press enter to execute a move, you can do many move inputs before executing.\n");
	creatWalls(0, 0);
}

//startcreateWalls
void creatWalls(int toprow, int leftcol)
{
	int ii, ic;
	int row = 6, col = 1;

	//for start
	for (ii = toprow; ii <= ROW; ii++)
	{
		//for start
		for (ic = leftcol; ic < COL; ic++)
		{
			//switch start
			switch (wall[ii][ic])
			{
			case 0:
			{
				//if start == top row
				if (ii == 0)
				{
					//if start
					if (wall[ii][ic - 1] == 203 || wall[ii][ic - 1] == 201)
					{
						wall[ii][ic] = 205;
						//endif
					}
					//elseif start
					else if (ic == 0)
					{
						wall[ii][ic] = 201;
						//endelseif
					}
					//else start
					else
					{
						wall[ii][ic] = (rand() % 8 == 1 ? 203 : 205);
						//endelse
					}
				}
				//start elseif == last two rows
				else if (ii >= ROW - 2)
				{
					//switch start
					switch (ii)
					{
					case ROW - 1:// Last row
					{
						//if start
						if (ic == 0)
						{
							wall[ii][ic] = 200;
							//endif
						}
						//else start
						else if (wall[ii - 1][ic] == 186)
						{
							wall[ii][ic] = 202;
							//endelse
						}
						//else start
						else
						{
							wall[ii][ic] = 205;
							//endelse
						}
						break;
						//endcase
					}
					case ROW - 2:// Second to last row
					{
						//if start
						if (wall[ii - 1][ic] == 210 || wall[ii - 1][ic] == 204 || wall[ii - 1][ic] == 201 || wall[ii - 1][ic] == 187 || wall[ii - 1][ic] == 186)
						{
							wall[ii][ic] = 186;
							//endif
						}
						//else start
						else
						{
							wall[ii][ic] = 0;
							//endelse
						}
						break;
						//endcase
					}
					//endswitch
					}
					//endelseif
				}
				//else start == the big space, the middle
				else
				{
					//if start == the far left column
					if (ic == 0)
					{
						//if start
						if (wall[ii - 1][ic] == 204 || wall[ii - 1][ic] == 201)
						{
							wall[ii][ic] = 186;
							//endif
						}
						//else start
						else
						{
							wall[ii][ic] = (rand() % 10 == 1 ? 204 : 186);
							//endelse
						}
						//endif
					}
					//elseif start == character placement
					else if (ii == 6 && ic == 1)
					{
						wall[ii][ic] = 2;
						wall[ii][ic - 1] = 186;
						//endelseif
					}
					//else start == the middle !(bottom, left, top)
					else
					{
						//switch start == check what's above
						switch (wall[ii - 1][ic])
						{
						case 210://D
						{
							//if start
							if (wall[ii][ic - 1] == 205 || wall[ii][ic - 1] == 201 || wall[ii][ic - 1] == 198)
							{
								wall[ii][ic] = 188;
								//endif
							}
							//elseif start
							else if (wall[ii][ic - 1] == 0 || wall[ii][ic - 1] == 2)
							{
								wall[ii][ic] = (rand() % 2 ? 200 : 186);
								//endelseif
							}
							break;
							//endcase
						}
						case 208://U
						{
							wall[ii][ic] = 0;
							break;
							//endcase
						}
						case 205://L + R
						{
							wall[ii][ic] = 0;
							break;
							//endcase
						}
						case 203://L, R, + D
						{
							wall[ii][ic] = 186;
							break;
							//endcase
						}
						case 201://R + D
						{
							//if start
							if (wall[ii][ic - 1] == 0 || wall[ii][ic - 1] == 2)
							{
								wall[ii][ic] = (rand() % 4 == 1 ? 208 : 186);
								//endif
							}
							//elseif start
							else if (wall[ii][ic - 1] == 201 || wall[ii][ic - 1] == 205 || wall[ii][ic - 1] == 198)
							{
								wall[ii][ic] = 188;
								//endelseif
							}
							break;
							//endcase
						}
						case 200://U + R
						{
							wall[ii][ic] = 0;
							break;
							//endcase
						}
						case 198://R
						{
							wall[ii][ic] = 0;
							break;
							//endcase
						}
						case 188://L + U
						{
							wall[ii][ic] = 0;
							break;
							//endcase
						}
						case 187://D + L
						{
							wall[ii][ic] = (rand() % 6 == 4 ? 200 : (rand() % 2 ? 208 : 186));
							break;
							//endcase
						}
						case 186://D + U
						{
							//if start
							if (wall[ii][ic - 1] == 0 || wall[ii][ic - 1] == 2)
							{
								wall[ii][ic] = (rand() % 3 ? 200 : 186);
								//endif
							}
							//elseif start
							else if (wall[ii][ic - 1] == 201 || wall[ii][ic - 1] == 198 || wall[ii][ic - 1] == 205)
							{
								wall[ii][ic] = 188;
							}
							break;
							//endcase
						}
						case 181://L
						{
							wall[ii][ic] = 0;
							break;
							//endcase
						}
						case 0://space
						{
							case0(ii, ic, 0);
							break;
							//endcase
						}
						//case start
						case 2://Character
						{
							case0(ii, ic, 0);
							break;
							//endcase
						}
						//endswitch
						}
						//endelse
					}
					//endelse
				}
				//endcase
			}
			//endswitch
			}
			//endfor ic
		}
		//endfor ii
	}
	if (leftcol == 0){
		theWalls(row, col);
	}
	//endcreateWalls
}

void BuildEnd(int row){
	for (; row < ROW; row++){
		if (row == 0)
		{
			if (wall[row][COL - 2] == 203)
				wall[row][COL - 1] = 205;
			else
				wall[row][COL - 1] = (rand() % 11 > 7 ? 203 : 205);
		}
		else if (row == ROW - 1)
		{
			if (wall[row][COL - 2] == 202)
				wall[row][COL - 1] = 205;
			else
				wall[row][COL - 1] = (rand() % 11 > 8 ? 202 : 205);
		}
		else
		{
			switch (wall[row - 1][COL - 1])
			{
			case 210://D
				if (wall[row][COL - 2] == 0){
					wall[row][COL - 2] = (rand() % 3 < 2 ? 200 : (rand() % 2 ? 208 : 186));
					if (wall[row][COL - 2] == (205 && 201 && 198)){
						wall[row][COL - 1] = (rand() % 4 > 2 ? 187 : 205);
					}
					else{
						wall[row][COL - 1] = 0;
					}
				}
				else if (wall[row][COL - 2] == (185 && 186 && 188 && 208))
					wall[row][COL - 1] = 0;
				else if (wall[row][COL - 2] == (204)){
					wall[row][COL - 1] = (rand() % 5 > 3 ? 181 : 205); //205 || 181
				}
				else if (wall[row][COL - 2] == (200 && 202)){
					wall[row][COL - 1] = (rand() % 5 > 3 ? (rand() % 4 > 2 ? 181 : 187) : (rand() % 4 > 2 ? 203 : 205));
				}
				break;
			case 208://U
				wall[row][COL - 1] = 0;
				break;
			case 205://L + R
				wall[row][COL - 1] = 0;
				break;
			case 201://L, R, + D
				if (wall[row][COL - 2] == 0 || wall[row][COL - 2] == 2)
					wall[row][COL - 1] = (rand() % 4 == 1 ? 208 : 186);
				else if (wall[row][COL - 2] == 201 || wall[row][COL - 2] == 205 || wall[row][COL - 2] == 198)
					wall[row][COL - 1] = 188;
				break;
			case 200://U + R
				wall[row][COL - 1] = 0;
				break;
			case 198://R
				wall[row][COL - 1] = 0;
				break;
			case 188://L + U
				wall[row][COL - 1] = 0;
				break;
			case 187://D + L
				wall[row][COL - 1] = (rand() % 5 ? 186 : 208);
				break;
			case 186://D + U
				if (wall[row][COL - 2])
					wall[row][COL - 1] = 188;
				else
					wall[row][COL - 1] = (rand() % 3 == 2 ? 200 : 208);
				break;
			case 181://L
				wall[row][COL - 1] = 0;
				break;
			case 0:
				case0(row, COL - 1, 1);
				break;
			}
		}
	}
}

void shift(int hor, int vert)
{
	int row, col;

	for (row = 0; row < ROW; row++)
	{
		for (col = 0; col < COL; col++)
		{
			if (col == COL - 1)
			{
				wall[row][col] = NULL;
			}
			else
				wall[row][col] = wall[row][col + 1];
		}
	}
	BuildEnd(0);
}


void case0(int ii, int ic, int RoL)
{
	if (RoL == 0)  //  For the initial maze creation
	{
		if (!wall[ii - 1][ic] || wall[ii - 1][ic] == 2)
		{
			//if start
			if (wall[ii][ic - 1] == 0 || wall[ii][ic - 1] == 2)
			{
				//if start
				if (wall[ii - 1][ic - 1] == 181 || wall[ii - 1][ic - 1] == 208 || wall[ii - 1][ic - 1] == 188)
				{
					wall[ii][ic] = 0;
					//endif
				}
				//elseif start
				else if (wall[ii - 1][ic + 1] == 0 || wall[ii - 1][ic + 1] == 200 || wall[ii - 1][ic + 1] == 198 ||
					wall[ii - 1][ic + 1] == 186 || wall[ii - 1][ic + 1] == 201 || wall[ii - 1][ic + 1] == 210 || wall[ii - 1][ic + 1] == 208)
				{
					//if start
					if (wall[ii - 1][ic + 1] == 200 || wall[ii - 1][ic + 1] == 198 || wall[ii - 1][ic + 1] == 208)
					{
						wall[ii][ic] = 0;
						//endif
					}
					//elseif start
					else if (wall[ii - 1][ic + 1] == 186)
					{
						wall[ii][ic] = 201;
						//endelseif
					}
					//else start
					else
					{
						wall[ii][ic] = (rand() % 6 ? 201 : 198);
						//endelse
					}
					//endelseif
				}
				//else start
				else
				{
					wall[ii][ic] = (rand() % 6 ? 201 : (rand() % 2 ? 210 : 198));
					//endelse
				}
				//endif
			}
			//elseif start
			else if (wall[ii][ic - 1] == 204 || wall[ii][ic - 1] == 201 || wall[ii][ic - 1] == 198)
			{
				//switch start
				switch (wall[ii][ic - 1])
				{
				case 201:
				{
					//if start
					if (wall[ii - 1][ic + 1] == 210 || wall[ii - 1][ic + 1] == 204 || wall[ii - 1][ic + 1] == 201 || wall[ii - 1][ic + 1] == 186 || wall[ii - 1][ic + 1] == 0)
					{
						wall[ii][ic] = 205;
						//endif
					}
					//elseif start
					else if (wall[ii - 1][ic + 1] == 198 || wall[ii - 1][ic + 1] == 200 || wall[ii - 1][ic + 1] == 208)
					{
						wall[ii][ic - 1] = 210;
						wall[ii][ic] = 0;
						//endelseif
					}
					break;
					//endcase
				}
				case 202:
				{
					wall[ii][ic] = 205;
					break;
					//endcase
				}
				case 204:
				{
					wall[ii][ic] = 205;
					break;
				}
				case 198:
				{
					if (wall[ii - 1][ic + 1] == 201 || wall[ii - 1][ic + 1] == 186 || wall[ii - 1][ic + 1] == 210)
						wall[ii][ic] = 205;
					else if (wall[ii - 1][ic + 1] == 200 || wall[ii - 1][ic + 1] == 208)
					{
						wall[ii][ic] = 0;
						wall[ii - 1][ic] = 0;
					}
					else
						wall[ii][ic] = (rand() % 2 ? (rand() % 2 ? 205 : 181) : 187);
					break;
					//endcase
				}
				//endswitch
				}
				//endelseif
			}
			//else start
			else
			{
				//if start
				if (wall[ii][ic - 1] == 200)
				{
					//if start
					if (wall[ii - 1][ic + 1] == 210 || wall[ii - 1][ic + 1] == 201 || wall[ii - 1][ic + 1] == 186)
					{
						wall[ii][ic] = 205;
						//endif
					}
					//else start
					else
					{
						wall[ii][ic] = (rand() % 6 ? 187 : 181);
						//endelse
					}
					//endif
				}
				//elseif start
				else if (wall[ii][ic - 1] == 205)
				{
					//if start
					if (!(wall[ii - 1][ic + 1] == 198 || wall[ii - 1][ic + 1] == 200 || wall[ii - 1][ic + 1] == 208))
					{
						wall[ii][ic] = (rand() % 5 ? 205 : 181);
						//start if
						if (wall[ii][ic] == 181 && wall[ii - 1][ic + 1])
						{
							//start if
							if (wall[ii - 1][ic + 1] == 186 || wall[ii - 1][ic + 1] == 201 || wall[ii - 1][ic + 1] == 210)
							{
								wall[ii][ic] = 205;
								//endif
							}
							//start else
							else
							{
								wall[ii - 1][ic + 1] = 0;
								wall[ii - 1][ic + 2] = 198;
								//endelse
							}
							//endif
						}
						//endif
					}
					//else start
					else{
						wall[ii][ic - 1] = 181;
						wall[ii][ic] = 0;
						//endelse
					}
					//endelseif
				}
				//else start
				else
				{
					wall[ii][ic] = 0;
					//endelse
				}
			}
		}
		//endCase0,2,+1
	}
	else  //  After the initial maze printing
	{
		if (wall[ii][ic - 1] == (0 && 2))
			if (wall[ii - 1][ic - 1])
			{
				if (wall[ii - 1][ic] == 187)
					wall[ii][ic] = (rand() % 2 ? 208 : (rand() % 2 ? 186 : 200));
				else
					wall[ii][ic] = 0;
			}
			else
				wall[ii][ic] = (rand() % 2 ? (rand() % 2 ? 201 : 210) : 198);
		else if (wall[ii][ic - 1])
		{
			if (wall[ii][ic - 1] == 198 || wall[ii][ic - 1] == 205)
				wall[ii][ic] = (rand() % 2 ? (rand() % 2 ? 205 : 188) : (rand() % 2 ? 187 : 181));
			else if (wall[ii][ic - 1] == 201)
				wall[ii][ic] = (rand() % 2 ? (rand() % 3 ? 205 : 181) : 188);
			else
				wall[ii][ic] = (rand() % 3 ? 205 : (rand() % 3 ? 187 : 181));

		}

		//endCase0,2,+1
	}
}


void theWalls(int row, int col)
{
	int ii, ic;
	static int suspend = 0;
	suspend++;
	if (suspend > 1)
		system("CLS");

	for (ii = 0; ii < ROW; ii++)
	{
		for (ic = 0; ic < COL; ic++)
		{
			cout << (char)wall[ii][ic];
		}
		cout << endl;
	}
	move(row, col);// variables are the posion of character
}


void move(int horizontal, int vertical) // variables are the position of character
{
	static char direction = 'q';
	static int count10 = 0;
	while (direction != ' ' && vertical != (COL - 1) && vertical != 0)
	{
		direction = _getch();
		switch (direction){
		case 'a':
		{
			if (wall[horizontal][vertical - 1])
			{
				count10++;
			}
			else
			{
				wall[horizontal][vertical - 1] = 2;
				wall[horizontal][vertical] = 0;
				vertical--;
				count10++;
			}
			break;
		}
		case 's':
		{
			if (wall[horizontal + 1][vertical])
			{
				count10++;
			}
			else
			{
				wall[horizontal + 1][vertical] = 2;
				wall[horizontal][vertical] = 0;
				horizontal++;
				count10++;
			}
			break;
		}
		case 'd':
		{
			if (wall[horizontal][vertical + 1])
			{
				count10++;
			}
			else
			{
				wall[horizontal][vertical + 1] = 2;
				wall[horizontal][vertical] = 0;
				vertical++;
				count10++;
			}
			break;
		}
		case 'w':
		{
			if (wall[horizontal - 1][vertical])
			{
				count10++;
			}
			else
			{
				wall[horizontal - 1][vertical] = 2;
				wall[horizontal][vertical] = 0;
				horizontal--;
				count10++;
			}
			break;
		}
		case ' ':
		{
			endGame();
			break;
		}
		}
		if (count10 == 10)
		{
			shift(horizontal, vertical);
			count10 = 0;
			vertical--;
		}
		if (vertical == COL - 1 || vertical == 0)
		{
			direction = ' ';
			endGame();
		}
		theWalls(horizontal, vertical);
	}
}

void endGame()
{

	cout << "YOU ARE ENDING THE GAME" << endl;
	_rmtmp();
	getchar();
	getchar();
}
