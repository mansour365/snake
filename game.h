//Different values for each direction, the values are meaningless and only need to be different
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2

//Set the max length of a snake
#define MAX 60

void initializeGrid(int, int);
void drawGrid();
void unit(int, int);
void drawSnake();
void drawFood();
void random(int&, int&);
