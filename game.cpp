#include <windows.h>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <ctime>
#include "game.h"



int gridX;
int gridY;

bool food = true;
int foodX, foodY;

short sDirection = RIGHT;
extern bool gameover;


int posX = 20, posY = 20;

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
	if (sDirection == UP){
		posY++;
	}
	else if (sDirection == DOWN){
		posY--;
	}
	else if (sDirection == RIGHT){
		posX++;
	}
	else if (sDirection == LEFT){
		posX--;
	}
	
	glColor3f(0.0, 1.0, 0.0);
	glRectd(posX, posY, posX + 1, posY + 1);
	if (posX == 0 || posX == gridX - 1 || posY == 0 || posY == gridY - 1)
	{
		gameover = true;
	}
	if (posX == foodX && posY == foodY)
	{
		food = true;
	}
}

void random(int &x, int &y)
{
	int maxValueX = gridX - 1;
	int maxValueY = gridY - 1;
	int minValue = 1;
	srand(time(NULL)); //return an integer number used to seed the random number
	x = rand() % maxValueX + minValue; //get random number from 1 to 38
	y = rand() % maxValueY + minValue;
}