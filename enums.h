#ifndef ENUMS_H
#define ENUMS_H

enum cell 
{
    BLANK = 0,
    WALL,
    SNAKE,
    SNAKE_HEAD,
    SNAKE_TALE,
    FOOD
};

enum direction 
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};

enum gameCondition
{
	NORMAL = 0,
	PAUSE,
	DEATH,
	GAMEOVER
};

#endif // ENUMS_H
