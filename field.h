#ifndef FIELD_H
#define FIELD_H

#include "enums.h"
#include <time.h>
#include <vector>

class field
{
public:
	int foodCount = 0;

    int fieldLength;
    int fieldWidth;

    cell **_field;

    field();

    field (const field &o);

    void spawnFood();

    ~field();
};

#endif // FIELD_H
