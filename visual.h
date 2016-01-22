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

	void gameOpenGLOut(snake mySnake, field myField);

    ~visual();
};

#endif // VISUAL_H
