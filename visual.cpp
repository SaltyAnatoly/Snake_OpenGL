#include "visual.h"
#include <glut.h>

visual::visual()
{
	Scale = 25;
}
void visual::gameOpenGLOut(snake mySnake, field myField)
{
	glClear(GL_COLOR_BUFFER_BIT);

	w = Scale*myField.fieldWidth;
	h = Scale*myField.fieldLength;

	glColor3f(0.7, 0.0, 0.7);
	glBegin(GL_LINES);
	for (int i = 0; i < w; i += Scale)
	{
		glVertex2f(i, 0); glVertex2f(i, h);
	}
	for (int j = 0; j < h; j += Scale)
	{
		glVertex2f(0, j); glVertex2f(w, j);
	}
	glEnd();

	for (int i = 0; i < myField.fieldLength; i++)
	{
		for (int j = 0; j < myField.fieldWidth; j++)
		{
			switch (myField._field[i][j]) {
			case  cell::WALL:
				glColor3f(0.2, 0.2, 0.7);
				break;
			case  cell::BLANK:
				glColor3f(0.0, 0.0, 0.0);
				break;
			case  cell::SNAKE:
				glColor3f(0.0, 0.4, 0.0);
				break;
			case  cell::SNAKE_HEAD:
				glColor3f(0.0, 0.9, 0.0);
				break;
			case  cell::SNAKE_TALE:
				glColor3f(0.0, 0.2, 0.0);
				break;
			case  cell::FOOD:
				glColor3f(0.8, 0.1, 0.1);
				break;
			}
			glRectf((j + 0.1)*Scale, (myField.fieldLength - i - 1 + 0.1)*Scale, (j + 0.9)*Scale, ((myField.fieldLength - i - 1) + 0.9)*Scale);
		}
	}

	glFlush();
	glutSwapBuffers();
}

visual::~visual()
{}
