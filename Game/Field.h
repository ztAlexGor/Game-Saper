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
	int Open(int x, int y, int* countMarks);
	Field(int h, int w, int countOfMines);
	int GetHeight();
	int GetWidth();
	int GetCellStatus(int x, int y);//0 - not open, 1 - opened, 2 - marked, 3 - взорвана;
	int GetCellNumber(int x, int y);
	int GetMinesCount();
	void win();
	void fail(int x, int y);
	bool DeleteMine(int x, int y);
	int AutoMark();
	int AutoOpen(int* countMarks);
	int Guess(int* countMarks);
	int GetCountOfClosed(int x, int y);
	int GetCountOfMarked(int x, int y);
	int MarkAll(int x, int y);
	int OpenAll(int x, int y, int* countMarks);
	int IsMarkTrue();
	float GetProb(int x, int y);
	float CountProb(int x, int y);
	~Field();
};