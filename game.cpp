#include <windows.h>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <ctime>
#include "game.h"



int gridX;
int gridY;

int snakeLength = 5;

bool food = true;
int foodX, foodY;

short sDirection = RIGHT;
extern bool gameover;


int posX[60] = { 20,20,20,20,20 }, posY[60] = {20,19,18,17,16};

void unit(int, int);

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
	if (x == 0 || y == 0 || x == gridX - 1 || y == gridY - 1)
	{
		glLineWidth(3.0);
		glColor3f(1.0, 0.0, 0.0);
	}
	else
	{
		glLineWidth(1.0);
		glColor3f(1.0, 1.0, 1.0);
	}

	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + 1, y);
	glVertex2f(x + 1, y + 1);
	glVertex2f(x, y + 1);
	glEnd();
}

void drawFood()
{
	if (food == true) {
		random(foodX, foodY);
	}
	food = false;
	glColor3f(1.0, 0.0, 0.0);
	glRectf(foodX, foodY, foodX + 1, foodY + 1);
		
}

void drawSnake()
{
	for (int i = snakeLength - 1; i > 0; i--)
	{
		posX[i] = posX[i - 1];
		posY[i] = posY[i - 1];
	}
	if (sDirection == UP){
		posY[0]++;
	}
	else if (sDirection == DOWN){
		posY[0]--;
	}
	else if (sDirection == RIGHT){
		posX[0]++;
	}
	else if (sDirection == LEFT){
		posX[0]--;
	}
	
	for (int i = 0; i < snakeLength; i++)
	{
		if (i == 0)
			glColor3f(0.0, 1.0, 0.0);
		else
			glColor3f(0.0, 0.0, 1.0);
		glRectd(posX[i], posY[i], posX[i] + 1, posY[i] + 1);
	}
	//only do collision detection for head element
	if (posX[0] == 0 || posX[0] == gridX - 1 || posY[0] == 0 || posY[0] == gridY - 1)
	{
		gameover = true;
	}
	//collision detection for the food
	if (posX[0] == foodX && posY[0] == foodY)
	{
		snakeLength++;
		if (snakeLength > MAX)
			snakeLength = MAX;

		food = true;
	}
}

void random(int &x, int &y)
{
	int maxValueX = gridX - 2;
	int maxValueY = gridY - 2;
	int minValue = 2;
	srand(time(NULL)); //return an integer number used to seed the random number
	x = rand() % maxValueX + minValue; //get random number from 1 to 38
	y = rand() % maxValueY + minValue;
}