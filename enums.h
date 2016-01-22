#ifndef ENUMS_H
#define ENUMS_H


enum cell {
    BLANK = 0,
    WALL,
    SNAKE,
    SNAKE_HEAD,
    SNAKE_TALE,
    FOOD
};

enum direction {
    UP = cell::FOOD + 1,
    DOWN,
    LEFT,
    RIGHT
};

#endif // ENUMS_H
