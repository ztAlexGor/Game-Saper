#pragma once
#include "Cell.h"

class Field {
	int height;
	int width;
	int countOfMines;
	Cell*** cells;

	int CalculateMines(int x, int y);
public:
	int SetSelfStatus(int x, int y);
	int Open(int x, int y);
	Field(int h, int w, int countOfMines);
	int GetHeight();
	int GetWidth();
	int GetCellStatus(int x, int y);//0 - not open, 1 - opened, 2 - marked, 3 - взорвана;
	int GetCellNumber(int x, int y);
	int GetMinesCount();
	void win();
	void fail(int x, int y);
	bool DeleteMine(int x, int y);
	~Field();
};