#pragma once
#include "Cell.h"

class Field {
	int height;
	int width;
	int countOfMines;
	Cell*** cells;
public:
	Field(int h, int w, int countOfMines);
	int GetHeight();
	int GetWidth();
	int GetCellStatus(int x, int y);//1 - has mine, 0 - empty cell
	~Field();
};