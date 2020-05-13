#include "Game.h"

Game::Game(int level) : level(level) {//constructor
    font.loadFromFile("Fonts/Calibri.ttf");
    solved = false;
    lose = false;

    if (level == 1) {
        pole = new Field{ 8, 10, 10 };//Easy level
    }
    else if (level == 2) {
        pole = new Field{ 13, 20, 40 };//Medium level
    }
    else if (level == 3) {
        pole = new Field{ 20, 33, 100 };//Hard level
    }

    countOfMarkes = pole->GetMinesCount();
    ClosedCells = (pole->GetHeight() * pole->GetWidth());
    /*else if (level == 4) {
      pole = new Field{ ,  , };//Custome level
    }*/
}

void Game::newGame(int level) {
    solved = false;
    lose = false;
    delete pole;
    if (level == 1) {
        pole = new Field{ 8, 10, 10 };//Easy level
    }
    else if (level == 2) {
        pole = new Field{ 13, 20, 40 };//Medium level
    }
    else if (level == 3) {
        pole = new Field{ 20, 33, 100 };//Hard level
    }
    countOfMarkes = pole->GetMinesCount();
    ClosedCells = (pole->GetHeight() * pole->GetWidth());
}

//Game::Game(const Game& other){//copy constructor
//  this->level = other.level;
//  this->solved = other.solved;
//  if (level == 1) {
//    pole = new Field{ 10, 8, 10 };//Easy level
//  }
//  else if (level == 2) {
//    pole = new Field{ 13, 20, 40 };//Medium level
//  }
//  else if (level == 3) {
//    pole = new Field{ 33, 20, 100 };//Hard level
//  }
//}

void Game::draw(RenderTarget& target, RenderStates states) const {
    states.transform *= getTransform();
    Color color = Color(127, 127, 127);

    // Рисуем меню игрового поля
    RectangleShape shape(Vector2f(pole->GetWidth() * Cell::size + 20.f, 40.f));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(color);
    shape.setFillColor(Color::Transparent);
    target.draw(shape, states);

    // Рисуем рамку игрового поля
    shape.setSize(Vector2f(pole->GetWidth() * Cell::size + 20.f, pole->GetHeight() * Cell::size + 60.f));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(color);
    shape.setFillColor(Color::Transparent);
    target.draw(shape, states);

    //// Подготавливаем рамку для отрисовки всех клеточек
    //shape.setSize(Vector2f(Cell::size - 2, Cell::size - 2));
    //shape.setOutlineThickness(2.f);
    //shape.setOutlineColor(color);
    //shape.setFillColor(Color::Transparent);

    // Подготавливаем текстовую заготовку для отрисовки чисел в клеточках

    Text text("", font, 18);
    text.setStyle(Text::Bold);

    text.setString(std::to_string(countOfMarkes));
    text.setPosition(Vector2f(15, 10));
    text.setFillColor(Color::Yellow);
    target.draw(text);

    Texture Texture;
    Texture.loadFromFile("Images/Cell.png");
    Sprite Cell;
    Cell.setTexture(Texture);


    for (unsigned int i = 0; i < pole->GetHeight(); i++) {
        for (unsigned int j = 0; j < pole->GetWidth(); j++) {
            text.setString("");
            if (pole->GetCellStatus(i, j) == 0) {// Не открытая клеточка
                Cell.setTextureRect(sf::IntRect(0, 0, 25, 25));
                text.setFillColor(color);
                int count = pole->GetCellNumber(i, j);
                if (count == 9) {
                    if (lose) {
                        Cell.setTextureRect(sf::IntRect(75, 0, 25, 25));
                    }
                    //else {//
                    //    text.setFillColor(Color::Black);
                    //    text.setString(std::to_string(count));
                    //}
                }
                //else if (count == 0)text.setString("");//
                //else text.setString(std::to_string(count));//
            }
            else if (pole->GetCellStatus(i, j) == 1) {//Уже открытая клеточка
                Cell.setTextureRect(sf::IntRect(25, 0, 25, 25));
                text.setFillColor(Color::Blue);
                int count = pole->GetCellNumber(i, j);
                if (count == 9)text.setFillColor(Color::Black);
                else if (count == 0)text.setString("");
                else text.setString(std::to_string(count));
            }
            else if (pole->GetCellStatus(i, j) == 2) {//Клеточка помечена как заминированная
                Cell.setTextureRect(sf::IntRect(50, 0, 25, 25));
            }
            else if (pole->GetCellStatus(i, j) == 3) {//Мина взорвана
                Cell.setTextureRect(sf::IntRect(100, 0, 25, 25));
            }

            // Вычисление позиции клеточки для отрисовки
            Vector2f position(j * Cell::size + 11.f, i * Cell::size + 52.f);
            Vector2f textPosition(j * Cell::size + 15.f, i * Cell::size + 50.f);

            text.setPosition(textPosition);
            Cell.setPosition(position);
            target.draw(Cell);
            target.draw(text, states);
        }
    }
    if (solved) {
        Text winText("YOU WON!!!", font, 50);
        winText.setStyle(Text::Bold);
        winText.setPosition(Vector2f(pole->GetWidth() * Cell::size / 2 - 110, pole->GetHeight() * Cell::size / 2 + 30));
        winText.setFillColor(Color(22, 114, 50));
        target.draw(winText);
    }
    else if (lose) {
        Text loseText("YOU LOSE :(", font, 40);
        loseText.setStyle(Text::Bold);
        loseText.setPosition(Vector2f(pole->GetWidth() * Cell::size / 2 - 80, pole->GetHeight() * Cell::size / 2 + 30));
        loseText.setFillColor(Color(255, 0, 0));
        target.draw(loseText);
    }
}

void Game::OpenCell(int x, int y) {
    if (pole->GetCellStatus(x, y) == 2)return;
    if (pole->GetCellNumber(x, y) == 9) {
        pole->fail(x, y);
        losing(0);
        return;
    }
    ClosedCells -= pole->Open(x, y);
    if (ClosedCells == pole->GetMinesCount())win();
}

int Game::GetLevel() {
    return level;
}

Game::~Game() {
    delete pole;
}

void Game::SetSelfStatus(int x, int y) {
    if (countOfMarkes == 0){
        if (pole->GetCellStatus(x, y) == 2) {
            pole->SetSelfStatus(x, y);
            countOfMarkes++;
        }
        return;
    }
    int a = pole->SetSelfStatus(x, y);
    if (a == 0)
        countOfMarkes++;
    else
        if (a == 1)
            countOfMarkes--;
}


int Game::getCountOfMarks(){
    return countOfMarkes;
}

void Game::win(){
    solved = true;
    pole->win();
    countOfMarkes = 0;
}

void Game::losing(int reason){
    lose = true;
}

bool Game::stop(){
    if (solved || lose)return true;
    else return false;
}
