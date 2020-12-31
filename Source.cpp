#include <windows.h>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "game.h"

#define ROWS 40
#define COLUMNS 40

#define FPS 10//might be too slow on the virtual machine (might need to increase this)

extern short sDirection;

bool gameover = false;

void timer(int);
void display();
void reshape(int, int);
void keyboard(int, int, int);

void init() 
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	initializeGrid(COLUMNS, ROWS); 
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); //initilize glut
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //initilize the display mode
	glutInitWindowSize(500, 500); //initilize the window size
	glutCreateWindow("Snake"); //Create the window
	glutReshapeFunc(reshape); //Reshape function

	glutTimerFunc(0, timer, 0);
	glutSpecialFunc(keyboard);

	init(); //initialize background color (before display())

	glutDisplayFunc(display); //register display callback

	glutMainLoop(); //mainloop

	return 0;
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT); //clear buffer at the begining of each frame

	drawGrid(); //draw the grid
	drawSnake(); //draw the snake
	drawFood(); //draw the food
	glutSwapBuffers();
	if (gameover == true)
	{
		MessageBoxA(NULL, "Your score is : ", "Game Over", 0);
		exit(0);
	}
}

//everytime program is resized, reset the viewport and projection of program
void reshape(int w, int h)
{
	//set viewport (top left coordinate (0,0), bottom right coordinates (w,h))
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	//a state variable to make it projection mode
	glMatrixMode(GL_PROJECTION);
	//No changes are made to the matrix in the begining
	glLoadIdentity();
	//Set up the projection (perspective or orthographic)
	glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
	//Switch back to model view matrix
	glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
	glutPostRedisplay(); //urge to call display funciton
	glutTimerFunc(1000 / FPS, timer, 0);
}

void keyboard(int key, int, int) 
{
	//make sure snake cant turn 180 degrees
	switch (key)
	{
	case GLUT_KEY_UP:
		if (sDirection != DOWN)
			sDirection = UP;
		break;
	case GLUT_KEY_DOWN:
		if (sDirection != UP)
			sDirection = DOWN;
		break;
	case GLUT_KEY_RIGHT:
		if (sDirection != LEFT)
			sDirection = RIGHT;
		break;
	case GLUT_KEY_LEFT:
		if (sDirection != RIGHT)
			sDirection = LEFT;
		break;
	}
}