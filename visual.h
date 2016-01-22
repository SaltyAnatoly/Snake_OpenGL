#ifndef VISUAL_H
#define VISUAL_H

#include "field.h"
#include "snake.h"
#include "windows.h"

class visual
{
public:
    visual();

	int Scale;

	int w;
	int h;

    HANDLE consoleHandle = 0;

    void gameConsoleOut(snake mySnake, field myField);

	void gameOpenGLOut(snake mySnake, field myField);

    void gameOverScreen(snake mySnake);

    ~visual();
};

#endif // VISUAL_H
