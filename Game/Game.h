#pragma once
#include "Header.h"
#include "Field.h"
#include "Cell.h"

using namespace sf;

class Game : public sf::Drawable, public sf::Transformable {
private:
    Font font;
    Texture Texture;
    int level;//easy, medium, hard, custome
    Field* pole;
    bool solved;
    bool lose;
    bool isGameRun;
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
    int getCountOfMarks();
    void win();
    void losing(int reason);//reason = 0 if player open the bomd and 1 if all time is waste
    bool GetIsGameRun();
    bool stop();
    ~Game();
};