#include "visual.h"
#include <glut.h>
#include <glaux.h>

visual::visual()
{
}

void visual::TextOut(int x, int y, char *string) 
{
	char *c; glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
	}
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
				glRectf((j + 0.1)*Scale, (myField.fieldLength - i - 1 + 0.1)*Scale, (j + 0.9)*Scale, ((myField.fieldLength - i - 1) + 0.9)*Scale);
				break;
			case  cell::BLANK:
				glColor3f(0.0, 0.0, 0.0);
				glRectf((j + 0.1)*Scale, (myField.fieldLength - i - 1 + 0.1)*Scale, (j + 0.9)*Scale, ((myField.fieldLength - i - 1) + 0.9)*Scale);
				break;
			case  cell::SNAKE:
				if (mySnake.dead)
				{
					if (blinking%2)
						glColor3f(0.0, 0.5, 0.0);
					else
						glColor3f(0.0, 0.3, 0.0);
				}
				else
					glColor3f(0.0, 0.4, 0.0);
				glRectf((j + 0.1)*Scale, (myField.fieldLength - i - 1 + 0.1)*Scale, (j + 0.9)*Scale, ((myField.fieldLength - i - 1) + 0.9)*Scale);
				break;
			case  cell::SNAKE_HEAD:
				if (mySnake.dead)
				{
					if (blinking % 2)
						glColor3f(0.0, 1.0, 0.0);
					else
						glColor3f(0.0, 0.8, 0.0);
				}
				else
					glColor3f(0.0, 0.9, 0.0);
				glRectf((j + 0.1)*Scale, (myField.fieldLength - i - 1 + 0.1)*Scale, (j + 0.9)*Scale, ((myField.fieldLength - i - 1) + 0.9)*Scale);
				break;
			case  cell::SNAKE_TALE:
				if (mySnake.dead)
				{
					if (blinking % 2)
						glColor3f(0.0, 0.3, 0.0);
					else
						glColor3f(0.0, 0.1, 0.0);
				}
				else
					glColor3f(0.0, 0.2, 0.0);
				glRectf((j + 0.1)*Scale, (myField.fieldLength - i - 1 + 0.1)*Scale, (j + 0.9)*Scale, ((myField.fieldLength - i - 1) + 0.9)*Scale);
				break;
			case  cell::FOOD:
				switch (blinking)
				{
				case 0:
				case 1:
				case 2:
					glColor3f(0.8, 0.1, 0.1);
					glRectf((j + 0.2)*Scale, (myField.fieldLength - i - 1 + 0.2)*Scale, (j + 0.8)*Scale, ((myField.fieldLength - i - 1) + 0.8)*Scale);
					blinking++;
					break;
				case 3:
				case 4:
				case 5:
					glColor3f(1.0, 0.1, 0.1);
					glRectf((j + 0.1)*Scale, (myField.fieldLength - i - 1 + 0.1)*Scale, (j + 0.9)*Scale, ((myField.fieldLength - i - 1) + 0.9)*Scale);
					if (blinking == 5)
						blinking = 0;
					else
						blinking++;
					break;
				}
				break;
			}
		}
	}
	
	glFlush();
	glutSwapBuffers();
}

void visual::overlayScreen(snake mySnake, int status)
{
	char str[10];
	_itoa_s(mySnake.points, str, 10);

	if (status == 0)
	{
		glColor3f(1.0, 0.0, 0.0);
		TextOut(w - 164, h - 18, "Your points: ");
		TextOut(w - 44, h - 18, str);
		glColor3f(0.0, 1.0, 0.0);
		TextOut(w - 166, h - 18, "Your points: ");
		TextOut(w - 46, h - 18, str);
		glColor3f(1.0, 1.0, 1.0);
		TextOut(w - 165, h - 18, "Your points: ");
		TextOut(w - 45, h - 18, str);
	}
	else if(status == 1)
	{
		glColor3f(1.0, 0.0, 0.0);
		TextOut(w / 2 - 11, h / 2 + 20, "PAUSE");
		TextOut(w / 2 - 61, h / 2 - 2, "Your points: ");
		TextOut(w / 2 - 64, h / 2 - 22, "Press ESC to exit");
		TextOut(w / 2 + 66, h / 2 - 2, str);
		glColor3f(0.0, 1.0, 0.0);
		TextOut(w / 2 - 9, h / 2 + 20, "PAUSE");
		TextOut(w / 2 - 59, h / 2 - 2, "Your points: ");
		TextOut(w / 2 - 62, h / 2 - 22, "Press ESC to exit");
		TextOut(w / 2 + 64, h / 2 - 2, str);
		glColor3f(1.0, 1.0, 1.0);
		TextOut(w / 2 - 10, h / 2 + 20, "PAUSE");
		TextOut(w / 2 - 60, h / 2 - 2, "Your points: ");
		TextOut(w / 2 - 63, h / 2 - 22, "Press ESC to exit");
		TextOut(w / 2 + 65, h / 2 - 2, str);
	}
	else if (status == 2)
	{
		glColor3f(1.0, 0.0, 0.0);
		TextOut(w / 2 - 25, h / 2 + 20, "YOU DIED");
		TextOut(w / 2 - 61, h / 2 - 2, "Your points: ");
		TextOut(w / 2 - 64, h / 2 - 22, "Press ESC to exit");
		TextOut(w / 2 + 66, h / 2 - 2, str);
		glColor3f(0.0, 1.0, 0.0);
		TextOut(w / 2 - 23, h / 2 + 20, "YOU DIED");
		TextOut(w / 2 - 59, h / 2 - 2, "Your points: ");
		TextOut(w / 2 - 62, h / 2 - 22, "Press ESC to exit");
		TextOut(w / 2 + 64, h / 2 - 2, str);
		glColor3f(1.0, 1.0, 1.0);
		TextOut(w / 2 - 24, h / 2 + 20, "YOU DIED");
		TextOut(w / 2 - 60, h / 2 - 2, "Your points: ");
		TextOut(w / 2 - 63, h / 2 - 22, "Press ESC to exit");
		TextOut(w / 2 + 65, h / 2 - 2, str);
	}
	else if (status == 3)
	{
		glColor3f(1.0, 0.0, 0.0);
		TextOut(w / 2 - 31, h / 2 + 20, "GAME OVER");
		TextOut(w / 2 - 61, h / 2 - 2, "Your points: ");
		TextOut(w / 2 - 94, h / 2 - 22, "Press ESC again to exit");
		TextOut(w / 2 + 66, h / 2 - 2, str);
		glColor3f(0.0, 1.0, 0.0);
		TextOut(w / 2 - 29, h / 2 + 20, "GAME OVER");
		TextOut(w / 2 - 59, h / 2 - 2, "Your points: ");
		TextOut(w / 2 - 92, h / 2 - 22, "Press ESC again to exit");
		TextOut(w / 2 + 64, h / 2 - 2, str);
		glColor3f(1.0, 1.0, 1.0);
		TextOut(w / 2 - 30, h / 2 + 20, "GAME OVER");
		TextOut(w / 2 - 60, h / 2 - 2, "Your points: ");
		TextOut(w / 2 - 93, h / 2 - 22, "Press ESC again to exit");
		TextOut(w / 2 + 65, h / 2 - 2, str);
	}

	glFlush();
	glutSwapBuffers();
}

visual::~visual()
{}
