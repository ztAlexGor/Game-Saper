#include "Cell.h"

class Field {
	int height;
	int width;
	Cell*** cells;
public:
	Field(int h, int w);
};