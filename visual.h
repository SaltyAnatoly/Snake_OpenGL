#ifndef VISUAL_H
#define VISUAL_H

#include "field.h"
#include "snake.h"
#include "windows.h"

class visual
{
public:
    visual();

	int Scale = 25;

	int blinking = 0;

	int w;
	int h;

	void gameOpenGLOut(snake mySnake, field myField);

	void overlayScreen(snake mySnake, int status);

	void TextOut(int x, int y, char *string);

    ~visual();
};

#endif // VISUAL_H
