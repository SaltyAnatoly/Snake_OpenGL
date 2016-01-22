#include "field.h"

field::field()
{
    srand(time(0));

    fieldLength = 20;
    fieldWidth = 40;

    _field = new cell*[fieldLength];
    for (int i = 0; i < fieldLength; i++)
        _field[i] = new cell [fieldWidth];

    for (int i = 0; i < fieldLength; i++)
        for (int j = 0; j < fieldWidth; j++)
            if(i == 0 || j == 0 || i == fieldLength - 1 || j == fieldWidth - 1)
                _field[i][j] = cell::WALL;
            else
                _field[i][j] = cell::BLANK;

    _field[fieldLength/2 - 1][0] = cell::BLANK;
    _field[fieldLength/2 - 1][fieldWidth - 1] =  cell::BLANK;
    _field[fieldLength/2][0] =  cell::BLANK;
    _field[fieldLength/2][fieldWidth - 1] =  cell::BLANK;
    _field[fieldLength/2 + 1][0] =  cell::BLANK;
    _field[fieldLength/2 + 1][fieldWidth - 1] =  cell::BLANK;

    _field[0][fieldWidth/2 - 1] =  cell::BLANK;
    _field[fieldLength - 1][fieldWidth/2 - 1] =  cell::BLANK;
    _field[0][fieldWidth/2] =  cell::BLANK;
    _field[fieldLength - 1][fieldWidth/2] =  cell::BLANK;
    _field[0][fieldWidth/2 + 1] =  cell::BLANK;
    _field[fieldLength - 1][fieldWidth/2 + 1] =  cell::BLANK;


    _field[1][1] =  cell::SNAKE;
}

field::field (const field &o)
{
    _field = new cell *[o.fieldLength];
    for (int i = 0; i < o.fieldLength; i++)
        _field[i] = new cell [o.fieldWidth];

    for (int i = 0; i < o.fieldLength; i++)
        for (int j = 0; j < o.fieldWidth; j++)
            _field[i][j] = o._field[i][j];

    fieldLength = o.fieldLength;
    fieldWidth = o.fieldWidth;
}

void field::spawnFood()
{
    int i;
    int j;

    do
    {
        i = rand() % (fieldLength - 2) + 1;
        j = rand() % (fieldWidth - 2) + 1;
    } while (_field[i][j] == cell::SNAKE || _field[i][j] == cell::SNAKE_TALE || _field[i][j] == cell::SNAKE_HEAD);

     _field[i][j] = cell::FOOD;

	 foodCount++;
}

field::~field()
{
    for (int i = 0; i < fieldLength; i++)
        delete [] _field[i];
    delete [] _field;
}
