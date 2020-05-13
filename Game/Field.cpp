#include "Field.h"
#include <ctime>
#include <iomanip>



void Field::Open(int x, int y){
	if (x < 0 || x >= height || y < 0 || y >= width)return;
	if (cells[x][y]->is_open == 1)return;
	cells[x][y]->is_open = 1;
	if (cells[x][y]->number > 0 && cells[x][y]->number < 9)return;

	if (x > 0 && y > 0)Open(x - 1, y - 1);
	if (x > 0)Open(x - 1, y);
	if (x > 0 && y < width - 1)Open(x - 1, y + 1);
	if (y > 0)Open(x, y - 1);
	if (y < width - 1 )Open(x, y + 1);
	if (x < height - 1 && y > 0)Open(x + 1, y - 1);
	if (x < height - 1)Open(x + 1, y);
	if (x < height - 1 && y < width - 1)Open(x + 1, y + 1);
}



Field::Field(int h, int w, int mines) : height(h), width(w), countOfMines(mines) {
	srand(time(NULL));
	cells = new Cell * *[height];
	for (int i = 0; i < height; i++) {
		cells[i] = new Cell * [width];
		for (int j = 0; j < width; j++)
			cells[i][j] = new Cell{ 0 };
	}

	for (int k = 0; k < countOfMines; k++) {
		int i = rand() % height;
		int j = rand() % width;
		if (cells[i][j]->number == 0) {
			cells[i][j]->number = 9;
		}
		else k--;
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (cells[i][j]->number != 9) {
				cells[i][j]->number = CalculateMines(i, j);
			}
		}
	}
}

int Field::GetHeight(){
	return height;
}

int Field::GetWidth(){
	return width;
}

int Field::GetCellStatus(int x, int y){
	return cells[x][y]->is_open;
}

int Field::GetCellNumber(int x, int y){
	return cells[x][y]->number;
}


Field::~Field(){
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			delete[] cells[i][j];
		delete[] cells[i];
	}
	delete[] cells;
}

int Field::CalculateMines(int x, int y) {
	int count = 0;
	if (x > 0 && y > 0 && cells[x - 1][y - 1]->number == 9)count++;
	if (x > 0 && cells[x - 1][y]->number == 9)count++;
	if (x > 0 && y < width - 1 && cells[x - 1][y + 1]->number == 9)count++;
	if (y > 0 && cells[x][y - 1]->number == 9)count++;
	if (y < width - 1 && cells[x][y + 1]->number == 9)count++;
	if (x < height - 1 && y > 0 && cells[x + 1][y - 1]->number == 9)count++;
	if (x < height - 1 && cells[x + 1][y]->number == 9)count++;
	if (x < height - 1 && y < width -1 && cells[x + 1][y + 1]->number == 9)count++;
	return count;
}

int Field::SetSelfStatus(int x, int y) {
	if (x < 0 || x >= height || y < 0 || y >= width) return -1;
	if (cells[x][y]->is_open == 2) {
		cells[x][y]->is_open = 0;
		return 0;
	}
	else
		if (cells[x][y]->is_open == 0) {
			cells[x][y]->is_open = 2;
			return 1;
		}
	return 2;
}
int Field::GetMinesCount() {
	return countOfMines;
}