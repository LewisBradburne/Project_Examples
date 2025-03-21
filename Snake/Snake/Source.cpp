#include <iostream>
#include <conio.h> //For the movement
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 30;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100]; //Creates an array with a max of 100 for the tail
int nTail; //Specifies the length of the tail
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN}; //For controls
eDirection dir;


void Setup()
{
	gameOver = false; //To keep the loop going
	dir = STOP;
	x = width / 2; //This is done to center the snake when the game starts by placing it directly in the middle
	y = width / 2;
	fruitX = rand() % width; //Random number is generated between 1 and width - 1, keeping it in the boundaries
	fruitY = rand() % height;
	score = 0;
}

void Draw() //methods for easier readability
{
	system("cls"); //Clears the console window, a little inefficient due to screen flickering
	for (int i = 0; i < width + 2; i++) //+2 added to fill in the corners
	{
		cout << "-";  //This generates the border for the top wall
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) //Two for loops needed as this part uses both variables
		{
			if (j == 0) //This is done as the character needs to be placed when width = 0 to be the left wall
			{
				cout << "|";
			}
			
			if (i == y && j == x)
			{
				cout << "0";
			}

			else if (i == fruitY && j == fruitX)
			{
				cout << "F";
			}

			else
			{
				bool print = false; //Keeps track of whether tail segment is printed
				for (int k = 0; k < nTail; k++) //Goes through every element in the tail
				{

					if (tailX[k] == j && tailY[k] == i) //If the X posiion of tail is equal to x-coordinate and tail y is equal to current y co-ordinate
					{
						cout << "o";
						print = true;
					}

					//if (!print) //If segment isn't printed
					//{
						//cout << " "; //Blank space used to pad out the arena the snake is in
					//}
				}
				
				if (!print) //If segment isn't printed
				{
					cout << " "; //Blank space used to pad out the arena the snake is in
				}
		
			}
			
			

			if (j == width - 1)
			{
				cout << "|";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
	{
		cout << "-";  //This generates the border for the bottom wall. It is the same and is put here to be run after the sides are created
	}

	cout << endl; //Inserts a new line of code
	cout << "Score:" << score << endl;
}

void Input()
{
	if (_kbhit()) //Returns a 1 if a keyboard button is pressed, basically a boolean operator
	{
		switch (_getch()) //Returns the ASCII value of the button pressed
		{
		case 'a': //For moving left when a is pressed
			dir = LEFT;
			break;

		case 'd': //For moving right
			dir = RIGHT;
			break;

		case 'w': //For moving up
			dir = UP;
			break;

		case 's': //For moving down
			dir = DOWN;
			break;

		case 'x': //For ending the game
			gameOver = true;
			break;
		}

	}
}

void Logic()
{
	int prevX = tailX[0]; //Remembers the last position of x
	int prevY = tailY[0]; //Remembers the last position of y
	int prev2X, prev2Y;

	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX; //Changes these values to keep the snake moving
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		x--; //Decreases the x value so that the snake moves left, like moving backwards across a line with numbers
		break;

	case RIGHT:
		x++; //Increases the x value so that the snake moves right, like moving forwards across a line with numbers
		break;

	case UP:
		y--; //Decreases the value of y so that the snake moves up
		break;

	case DOWN:
		y++; //Increases the value of y so that the snake moves up
		break;

	default:
		break;

	}

	if (x > width || x < 0 || y > height || y < 0) //Ends the game if x is greater than width,if x is less than 0, if y is greater than height or if y id less than 0
	{
		gameOver = true;
	}

	if (x == fruitX && y == fruitY)
	{
		score += 10; //Boosts the score by 10
		fruitX = rand() % width; //Same code as earlier to create a new fruit 
		fruitY = rand() % height;
		nTail++; //Increments tail by one when food is grabbed
	}

}


int main()
{
	Setup();
	while (gameOver == false)
	{
		Draw();
		Input();
		Logic();
		Sleep(100);
	}
	return 0;
}