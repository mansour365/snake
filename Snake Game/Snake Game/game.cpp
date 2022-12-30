#include <windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ctime>
#include "game.h"

extern int score;

int gridX;
int gridY;

//initial length of the snake
int snakeLength = 5;

bool spawnfood = true;
int foodX, foodY;

short sDirection = RIGHT;
extern bool gameover;


int posX[60] = { 20,20,20,20,20 }, posY[60] = { 20,19,18,17,16 };



//Initializes the gridX and gridY variables with the number of rows and columns set by the user
void initializeGrid(int x, int y)
{
	gridX = x;
	gridY = y;
}

void drawGrid()
{
	for (int i = 0; i < gridX; i++)
	{
		for (int j = 0; j < gridY; j++)
		{
			unit(i, j);
		}
	}
}

void unit(int x, int y)
{
	//check if the unit square is on the boarders, if it is then it is red
	if (x == 0 || y == 0 || x == gridX - 1 || y == gridY - 1)
	{
		glLineWidth(3.0);
		glColor3f(1.0, 0.0, 0.0);
	}
	//otherwise unit squares are grey
	else
	{
		glLineWidth(1.0);
		glColor3f(0.5, 0.5, 0.5);
	}
	//draw the unit square using 4 vertices based on the iteration of the nested for loop
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + 1, y);
	glVertex2f(x + 1, y + 1);
	glVertex2f(x, y + 1);
	glEnd();
}

void drawFood()
{
	//if need spawn new food in new location call the random function
	if (spawnfood == true) {
		random(foodX, foodY);
	}
	//set the spawn boolean back to false, until it is changed again (when a snake eats it)
	spawnfood = false;
	//draw the food based on the random function location
	glColor3f(1.0, 0.0, 0.0);
	glRectf(foodX, foodY, foodX + 1, foodY + 1);

}

void random(int& x, int& y)
{
	int maxValueX = gridX - 3;
	int maxValueY = gridY - 3;
	int minValue = 2;
	srand(time(NULL)); //return an integer number used to seed the random number
	x = rand() % maxValueX + minValue; //random number from 1 to 38
	y = rand() % maxValueY + minValue;
}

void drawSnake()
{
	//Make the previous elements of snake follow the elements before them
	for (int i = snakeLength - 1; i > 0; i--)
	{
		posX[i] = posX[i - 1];
		posY[i] = posY[i - 1];
	}

	//move the head of snake depending on direction (update position once per frame)
	if (sDirection == UP) {
		posY[0]++;
	}
	else if (sDirection == DOWN) {
		posY[0]--;
	}
	else if (sDirection == RIGHT) {
		posX[0]++;
	}
	else if (sDirection == LEFT) {
		posX[0]--;
	}

	//draw the snake using opengl
	for (int i = 0; i < snakeLength; i++)
	{
		if (i == 0)
			glColor3f(0.0, 1.0, 0.0);
		else
			glColor3f(0.0, 0.5, 0.0);

		glRectd(posX[i], posY[i], posX[i] + 1, posY[i] + 1);
	}

	//check collision with tail
	for (int j = 1; j < snakeLength; j++)
	{
		if (posX[j] == posX[0] && posY[j] == posY[0])
			gameover = true;
	}
	//collision detection for head element and game boundaries
	if (posX[0] == 0 || posX[0] == gridX - 1 || posY[0] == 0 || posY[0] == gridY - 1)
	{
		gameover = true;
	}
	//collision detection for the food
	if (posX[0] == foodX && posY[0] == foodY)
	{
		score++;
		snakeLength++;
		if (snakeLength > MAX)
			snakeLength = MAX;

		spawnfood = true;
	}
}


