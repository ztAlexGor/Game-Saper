#include "Field.h"
#include <ctime>
#include <iomanip>

Field::Field(int h, int w) : height(h), width(w) {
	srand(time(NULL));
	cells = new Cell * *[height];
	for (int i = 0; i < height; i++)
		cells[i] = new Cell * [width];

	int count = height * width/*???*/; // suda dobav formulu dlya colichestva min na pole)

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			cells[i][j] = nullptr;

	for (int k = 0; k < count; k++) {
		bool a = true;
		while (a == true) {
			int i = rand() % height;
			int j = rand() % width;
			if (cells[i][j] == nullptr) {
				cells[i][j] = new Mine;
				a = false;
			}
		}
	}
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (cells[i][j] == nullptr)
				cells[i][j] = new Empty;
}