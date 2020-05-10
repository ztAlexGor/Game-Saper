

class Cell {
protected:
	int is_open; // 0 - not open, 1 - marked, 2 - opened;
};

class Mine : public Cell {
public:
	Mine();
};

class Empty : public Cell {

public:
	Empty();
};