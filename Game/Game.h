#pragma once
#include "Header.h"
#include "Field.h"
#include "Cell.h"

using namespace sf;

class Game : public sf::Drawable, public sf::Transformable {
private:
    Font font;
    int level;//easy, medium, hard, custome
    Field* pole;
    bool solved;
    int countOfMarkes;
    int ClosedCells;
public:
    Game(int level);
    void newGame(int level);
    //Game(const Game& other);
    virtual void draw(RenderTarget& target, RenderStates states)const;
    void OpenCell(int x, int y);
    int GetLevel();
    void SetSelfStatus(int x, int y);
    void DeCrement();
    int getCountOfMarks();
    ~Game();
};