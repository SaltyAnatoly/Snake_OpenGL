#ifndef SNAKE_H
#define SNAKE_H

#include "field.h"
#include <vector>
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

    int points = 0;

	bool dead = 0;

    snake();

    void snakeMoving(field &myField);

	void catchKeyButton(int key);

	void killNode();

	~snake();

private:
	const int moveUp = 101, moveDown = 103, moveRight = 102, moveLeft = 100;

	int currentDirection = DOWN;

	int keyButton;

	void movingSnakeNodes();
};

#endif // SNAKE_H
