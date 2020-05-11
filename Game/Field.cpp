#include "Field.h"
#include <ctime>
#include <iomanip>

Field::Field(int h, int w, int mines) : height(h), width(w), countOfMines(mines) {
	srand(time(NULL));
	cells = new Cell * *[height];
	for (int i = 0; i < height; i++) {
		cells[i] = new Cell * [width];
		for (int j = 0; j < width; j++)
			cells[i][j] = nullptr;
	}

	for (int k = 0; k < countOfMines; k++) {
		int i = rand() % height;
		int j = rand() % width;
		if (cells[i][j] == nullptr) {
			cells[i][j] = new Mine;
		}
		else k--;
	}
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (cells[i][j] == nullptr)
				cells[i][j] = new Empty;
}

int Field::GetHeight(){
	return height;
}

int Field::GetWidth(){
	return width;
}

int Field::GetCellStatus(int x, int y){
	if (cells[x][y] == 0) {
		return 0;
	}
	else{// if (typeid(cells[x][y]) == typeid(Mine)) {
		return 1;
	}
}

Field::~Field(){
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			delete[] cells[i][j];
		delete[] cells[i];
	}
	delete[] cells;
}
