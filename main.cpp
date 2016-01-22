//LIBS += -lncurses

#include <iostream>
#include "field.h"
#include "snake.h"
#include "visual.h"
#include <glut.h>

field myField;

snake mySnake;

visual vis;

void updateField()
{
	for (int i = 0; i < myField.fieldLength; i++)
		for (int j = 0; j < myField.fieldWidth; j++)
			if (myField._field[i][j] != cell::FOOD && myField._field[i][j] != cell::WALL)
				myField._field[i][j] = cell::BLANK;

	for (int s = 0; s < mySnake.snakeLength; s++)
		myField._field[mySnake._snake[s].iCurrentPosition][mySnake._snake[s].jCurrentPosition] = cell::SNAKE;
	myField._field[mySnake._snake[0].iCurrentPosition][mySnake._snake[0].jCurrentPosition] = cell::SNAKE_HEAD;

	if (mySnake.snakeLength > 1)
		myField._field[mySnake._snake[mySnake.snakeLength - 1].iCurrentPosition][mySnake._snake[mySnake.snakeLength - 1].jCurrentPosition] = cell::SNAKE_TALE;
}

void display()
{
	vis.gameOpenGLOut(mySnake, myField);
}

void processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

void KeyboardEvent(int caughtKey, int a, int b)
{
	mySnake.snakeKeyButtonPushed(caughtKey);
}

void Tick()
{
	mySnake.snakeMoving(myField);

	if (mySnake.isSnakeEatTheFood)
		myField.foodCount--;

	if (myField.foodCount == 0)
	{
		myField.spawnFood();
		mySnake.isSnakeEatTheFood = 0;
	}

	updateField();
		
	if (mySnake.dead == 1)
		exit(0);
}

void timer(int = 0)
{
	Tick();

	display();

	glutTimerFunc(70, timer, 0);
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(myField.fieldWidth*vis.Scale, myField.fieldLength*vis.Scale);
	glutCreateWindow("TOP IGRUHA SHEDEVR VASCHE ATVICHAYU");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, myField.fieldWidth*vis.Scale, 0, myField.fieldLength*vis.Scale);

	myField.spawnFood();
	display();

	glutDisplayFunc(display);
	glutSpecialFunc(KeyboardEvent);
	glutKeyboardFunc(processNormalKeys);
	glutTimerFunc(70, timer, 0);

	glutMainLoop();
}
