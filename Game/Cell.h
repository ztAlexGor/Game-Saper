#pragma once

class Cell {
public:
	int number;//0-8 cell without mine; 9 - is mine;
	int is_open; // 0 - not open, 1 - opened, 2 - marked, 3 - взорвана;
	static const int size = 25;
	Cell(int number);
};