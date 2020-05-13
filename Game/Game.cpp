#include "Game.h"

Game::Game(int level) : level(level) {//constructor
    font.loadFromFile("Fonts/Calibri.ttf");

    if (level == 1) {
        pole = new Field{ 8, 10, 10 };//Easy level
    }
    else if (level == 2) {
        pole = new Field{ 13, 20, 40 };//Medium level
    }
    else if (level == 3) {
        pole = new Field{ 20, 33, 100 };//Hard level
    }

    countOfMarkes = pole->GetMinesCount;
    ClosedCells = (pole->GetHeight * pole->GetWidth) - countOfMarkes;
    /*else if (level == 4) {
      pole = new Field{ ,  , };//Custome level
    }*/
}

void Game::newGame(int level) {
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
    countOfMarkes = pole->GetMinesCount;
    ClosedCells = (pole->GetHeight * pole->GetWidth) - countOfMarkes;
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
    Color color = Color(200, 100, 200);

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

    Texture NotOpenCellTexture;
    Sprite Cell;

    for (unsigned int i = 0; i < pole->GetHeight(); i++) {
        for (unsigned int j = 0; j < pole->GetWidth(); j++) {
            text.setString("");
            if (pole->GetCellStatus(i, j) == 0) {// Не открытая клеточка
                NotOpenCellTexture.loadFromFile("Images/Kletka.png");
                Cell.setTexture(NotOpenCellTexture);

                text.setFillColor(Color::Blue);
                text.setString(std::to_string(pole->GetCellNumber(i, j)));
                if (pole->GetCellNumber(i, j) == 9)text.setFillColor(Color::Black);
                if (pole->GetCellNumber(i, j) == 0)text.setString("");
            }
            else if (pole->GetCellStatus(i, j) == 1) {//Уже открытая клеточка
                NotOpenCellTexture.loadFromFile("Images/Kletka.png");
                Cell.setTexture(NotOpenCellTexture);
                text.setFillColor(Color::Magenta);
                text.setString(std::to_string(pole->GetCellNumber(i, j)));
                if (pole->GetCellNumber(i, j) == 0)text.setString("");
            }
            else if (pole->GetCellStatus(i, j) == 2) {//Клеточка помечена как заминированная
                NotOpenCellTexture.loadFromFile("Images/Kletka.png");
                Cell.setTexture(NotOpenCellTexture);
                text.setFillColor(Color::Red);
                text.setString("1");
            }
            else if (pole->GetCellStatus(i, j) == 3) {//Мина взорвана
                NotOpenCellTexture.loadFromFile("Images/Kletka.png");
                Cell.setTexture(NotOpenCellTexture);
                text.setFillColor(Color::Black);
                text.setString("");
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
}

void Game::OpenCell(int x, int y) {
    pole->Open(x, y);
}

int Game::GetLevel() {
    return level;
}

Game::~Game() {
    delete pole;
}

void Game::SetSelfStatus(int x, int y) {
    pole->SetSelfStatus(x, y);
}

void Game::DeCrement() {
    countOfMarkes--;
}

int Game::getCountOfMarks()
{
    return countOfMarkes;
}
