#ifndef SNAKE_H
#define SNAKE_H

#include "field.h"
//#include <ncurses.h>
#include <conio.h>
#include <vector>
#include <iostream>
#include "windows.h"

class snake
{
public:
    struct snakeNode
    {
        int iCurrentPosition;
        int jCurrentPosition;
    };

    std::vector <snakeNode> _snake;

    int snakeLength;

    bool isSnakeEatTheFood = 0;

    int waitTime = 100;

    int points = 0;

    snake();

	bool dead = 0;

	int keyButton;

    void snakeMoving(field &myField);

    ~snake();

    const int moveUp = 101, moveDown = 103, moveRight = 102, moveLeft = 100;

    int currentDirection = DOWN;

    void snakeMove();

	void snakeKeyButtonPushed(int key);
};

#endif // SNAKE_H
