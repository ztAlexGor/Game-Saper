#include "Field.h"
#include <ctime>
#include <iomanip>



int Field::Open(int x, int y, int* countMarks){
	if (x < 0 || x >= height || y < 0 || y >= width)return 0;
	if (cells[x][y]->is_open == 1)return 0;

	if (cells[x][y]->is_open == 2)(*countMarks)++;
	cells[x][y]->is_open = 1;
	int col = 1;
	if (cells[x][y]->number > 0 && cells[x][y]->number < 9)return col;

	if (x > 0 && y > 0)col += Open(x - 1, y - 1, countMarks);
	if (x > 0)col += Open(x - 1, y, countMarks);
	if (x > 0 && y < width - 1)col += Open(x - 1, y + 1, countMarks);
	if (y > 0)col += Open(x, y - 1, countMarks);
	if (y < width - 1 )col += Open(x, y + 1, countMarks);
	if (x < height - 1 && y > 0)col += Open(x + 1, y - 1, countMarks);
	if (x < height - 1)col += Open(x + 1, y, countMarks);
	if (x < height - 1 && y < width - 1)col += Open(x + 1, y + 1, countMarks);
	return col;
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
	if (x < 0 || x >= height || y < 0 || y >= width)return -1;
	return cells[x][y]->is_open;
}

int Field::GetCellNumber(int x, int y){
	if (x < 0 || x >= height || y < 0 || y >= width)return -1;
	return cells[x][y]->number;
}

int Field::AutoMark() {
	int count = 0;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			if (cells[i][j]->is_open == 1) {
				if (cells[i][j]->number == GetCountOfClosed(i, j)) {
					count += MarkAll(i, j);
				}
			}
		}
	return count;
}

int Field::AutoOpen(int* countMarks) {
	int count = 0;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			if (cells[i][j]->is_open == 1)
				if (cells[i][j]->number == GetCountOfMarked(i, j)) {
					count += OpenAll(i, j, countMarks);
				}
		}
	return count;
}

int Field::Guess(int* countMarks) {
	int x = -1, y = -1, min = 10;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			if (cells[i][j]->is_open == 0 && cells[i][j]->number != 9 && min > GetCountOfClosed(i,j)) {
				min = GetCountOfClosed(i, j);
				x = i;
				y = j;
			}
		}
	if (x == -1 || y == -1)return -1;
	return this->Open(x, y, countMarks);
}

int Field::GetCountOfClosed(int x, int y) {
	int count = 0;
	if (x > 0 && y > 0 && cells[x - 1][y - 1]->is_open != 1)count++;
	if (x > 0 && cells[x - 1][y]->is_open != 1)count++;
	if (x > 0 && y < width - 1 && cells[x - 1][y + 1]->is_open != 1)count++;
	if (y > 0 && cells[x][y - 1]->is_open != 1)count++;
	if (y < width - 1 && cells[x][y + 1]->is_open != 1)count++;
	if (x < height - 1 && y > 0 && cells[x + 1][y - 1]->is_open != 1)count++;
	if (x < height - 1 && cells[x + 1][y]->is_open != 1)count++;
	if (x < height - 1 && y < width - 1 && cells[x + 1][y + 1]->is_open != 1)count++;
	return count;
}

int Field::GetCountOfMarked(int x, int y) {
	int count = 0;
	if (x > 0 && y > 0 && cells[x - 1][y - 1]->is_open == 2)count++;
	if (x > 0 && cells[x - 1][y]->is_open == 2)count++;
	if (x > 0 && y < width - 1 && cells[x - 1][y + 1]->is_open == 2)count++;
	if (y > 0 && cells[x][y - 1]->is_open == 2)count++;
	if (y < width - 1 && cells[x][y + 1]->is_open == 2)count++;
	if (x < height - 1 && y > 0 && cells[x + 1][y - 1]->is_open == 2)count++;
	if (x < height - 1 && cells[x + 1][y]->is_open == 2)count++;
	if (x < height - 1 && y < width - 1 && cells[x + 1][y + 1]->is_open == 2)count++;
	return count;
}

int Field::MarkAll(int x, int y) {
	int count = 0;
	if (x > 0 && y > 0 && cells[x - 1][y - 1]->is_open == 0) { cells[x - 1][y - 1]->is_open = 2; count++;}
	if (x > 0 && cells[x - 1][y]->is_open == 0){cells[x - 1][y]->is_open = 2; count++;}
	if (x > 0 && y < width - 1 && cells[x - 1][y + 1]->is_open == 0) { cells[x - 1][y + 1]->is_open = 2; count++; }
	if (y > 0 && cells[x][y - 1]->is_open == 0) { cells[x][y - 1]->is_open = 2; count++; }
	if (y < width - 1 && cells[x][y + 1]->is_open == 0) { cells[x][y + 1]->is_open = 2; count++; }
	if (x < height - 1 && y > 0 && cells[x + 1][y - 1]->is_open == 0) { cells[x + 1][y - 1]->is_open = 2; count++; }
	if (x < height - 1 && cells[x + 1][y]->is_open == 0) { cells[x + 1][y]->is_open = 2; count++; }
	if (x < height - 1 && y < width - 1 && cells[x + 1][y + 1]->is_open == 0) { cells[x + 1][y + 1]->is_open = 2; count++; }
	return count;
}

int Field::OpenAll(int x, int y, int* countMarks) {
	int count = 0;
	if (x > 0 && y > 0 && cells[x - 1][y - 1]->is_open != 2) count += Open(x - 1, y - 1, countMarks);
	if (x > 0 && cells[x - 1][y]->is_open != 2)Open(x - 1, y, countMarks);
	if (x > 0 && y < width - 1 && cells[x - 1][y + 1]->is_open != 2) count += Open(x - 1, y + 1, countMarks);
	if (y > 0 && cells[x][y - 1]->is_open != 2) count += Open(x, y - 1, countMarks);
	if (y < width - 1 && cells[x][y + 1]->is_open != 2) count += Open(x, y + 1, countMarks);
	if (x < height - 1 && y > 0 && cells[x + 1][y - 1]->is_open != 2) count += Open(x + 1, y - 1, countMarks);
	if (x < height - 1 && cells[x + 1][y]->is_open != 2) count += Open(x + 1, y, countMarks);
	if (x < height - 1 && y < width - 1 && cells[x + 1][y + 1]->is_open != 2) count += Open(x + 1, y + 1, countMarks);
	return count;
}

int Field::IsMarkTrue() {
	int count = 0;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (cells[i][j]->is_open == 2 && cells[i][j]->number != 9) {
				cells[i][j]->is_open = 0;
				count++;
			}
	return count;
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

void Field::win(){
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (cells[i][j]->number == 9) {
				cells[i][j]->is_open = 2;
			}
		}
	}
}

void Field::fail(int x, int y){
	if (x < 0 || x >= height || y < 0 || y >= width) return;
	cells[x][y]->is_open = 3;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (cells[i][j]->number != 9){
				cells[i][j]->is_open = 1;
			}
		}
	}
}

bool Field::DeleteMine(int x, int y){
	if (x < 0 || x >= height || y < 0 || y >= width) return false;
	bool u = true;
	int i;
	int j;
	while (u){
		i = rand() % height;
		j = rand() % width;
		if (cells[i][j]->number != 9) {
			cells[i][j]->number = 9;
			u = false;
		}
	}
	cells[x][y]->number = CalculateMines(x, y);
	{
		if (x > 0 && y > 0 && cells[x - 1][y - 1]->number != 9)cells[x - 1][y - 1]->number--;
		if (x > 0 && cells[x - 1][y]->number != 9)cells[x - 1][y]->number--;
		if (x > 0 && y < width - 1 && cells[x - 1][y + 1]->number != 9)cells[x - 1][y + 1]->number--;
		if (y > 0 && cells[x][y - 1]->number != 9)cells[x][y - 1]->number--;
		if (y < width - 1 && cells[x][y + 1]->number != 9)cells[x][y + 1]->number--;
		if (x < height - 1 && y > 0 && cells[x + 1][y - 1]->number != 9)cells[x + 1][y - 1]->number--;
		if (x < height - 1 && cells[x + 1][y]->number != 9)cells[x + 1][y]->number--;
		if (x < height - 1 && y < width - 1 && cells[x + 1][y + 1]->number != 9)cells[x + 1][y + 1]->number--;
	}
	x = i; y = j;
	{
		if (x > 0 && y > 0 && cells[x - 1][y - 1]->number != 9)cells[x - 1][y - 1]->number++;
		if (x > 0 && cells[x - 1][y]->number != 9)cells[x - 1][y]->number++;
		if (x > 0 && y < width - 1 && cells[x - 1][y + 1]->number != 9)cells[x - 1][y + 1]->number++;
		if (y > 0 && cells[x][y - 1]->number != 9)cells[x][y - 1]->number++;
		if (y < width - 1 && cells[x][y + 1]->number != 9)cells[x][y + 1]->number++;
		if (x < height - 1 && y > 0 && cells[x + 1][y - 1]->number != 9)cells[x + 1][y - 1]->number++;
		if (x < height - 1 && cells[x + 1][y]->number != 9)cells[x + 1][y]->number++;
		if (x < height - 1 && y < width - 1 && cells[x + 1][y + 1]->number != 9)cells[x + 1][y + 1]->number++;
	}
	return true;
}
