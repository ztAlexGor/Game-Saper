#pragma once
#include "Header.h"
#include "Field.h"
#include "Cell.h"

using namespace sf;

class Game : public sf::Drawable, public sf::Transformable {
private:
	int level;//easy, medium, hard, custome
	Field *pole;
	bool solved;
public:
	Game(int level);
	void newGame(int level);
	//Game(const Game& other);
	virtual void draw(RenderTarget& target, RenderStates states)const;
	void OpenCell(int x, int y);
	int GetLevel();
	~Game();
};