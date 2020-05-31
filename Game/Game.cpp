#include "Game.h"

Game::Game(int level) : level(level) {//constructor
    font.loadFromFile("Fonts/Calibri.ttf");
    Texture.loadFromFile("Images/Cell.png");
    solved = false;
    lose = false;
    isGameRun = false;

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
    this->level = level;
    solved = false;
    lose = false;
    isGameRun = false;
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

void Game::newGame(int w, int h, int m){
    this->level = 4;
    solved = false;
    lose = false;
    isGameRun = false;
    delete pole;
    pole = new Field{ h, w, m };//Easy level
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


    // Рисуем рамку игрового поля
   /* RectangleShape shape(Vector2f(pole->GetWidth() * Cell::size, pole->GetHeight() * Cell::size + 50.f));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(color);
    shape.setFillColor(Color(139, 250, 131));
    target.draw(shape, states);*/

    // Рисуем меню игрового поля
    /*shape.setSize(Vector2f(pole->GetWidth() * Cell::size, 40.f));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(color);
    shape.setFillColor(Color::Transparent);
    target.draw(shape, states);*/

   /* shape.setSize(Vector2f(pole->GetWidth() * Cell::size - 2, pole->GetHeight() * Cell::size - 2));
    shape.setPosition(Vector2f(10, 50));
    shape.setOutlineThickness(6.f);
    shape.setOutlineColor(Color(70, 70, 70));
    target.draw(shape, states);*/

    //// Подготавливаем рамку для отрисовки всех клеточек
    //shape.setSize(Vector2f(Cell::size - 2, Cell::size - 2));
    //shape.setOutlineThickness(2.f);
    //shape.setOutlineColor(color);
    //shape.setFillColor(Color::Transparent);

    // Подготавливаем текстовую заготовку для отрисовки чисел в клеточках

    Text text("", font, 18);
    text.setStyle(Text::Bold);

    text.setString(std::to_string(countOfMarkes));
    text.setPosition(Vector2f(62, 36));
    text.setFillColor(Color::Red);
    target.draw(text);

    
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
            Vector2f position(j * Cell::size + 10, i * Cell::size + 81.f);
            Vector2f textPosition(j * Cell::size + 17.f, i * Cell::size + 81.f);

            text.setPosition(textPosition);
            Cell.setPosition(position);
            target.draw(Cell);
            target.draw(text, states);
        }
    }
    if (solved) {
        Text winText("YOU WON!!!", font, 50);
        winText.setStyle(Text::Bold);
        winText.setPosition(Vector2f(pole->GetWidth() * Cell::size / 2 - 110, pole->GetHeight() * Cell::size / 2 + 56));
        winText.setFillColor(Color(22, 114, 50));
        target.draw(winText);
    }
    else if (lose) {
        Text loseText("YOU LOSE :(", font, 40);
        loseText.setStyle(Text::Bold);
        loseText.setPosition(Vector2f(pole->GetWidth() * Cell::size / 2 - 80, pole->GetHeight() * Cell::size / 2 + 56));
        loseText.setFillColor(Color(255, 0, 0));
        target.draw(loseText);
    }
}

void Game::OpenCell(int x, int y) {
    if (pole->GetCellStatus(x, y) == 2)return;
    if (pole->GetCellNumber(x, y) == 9) {
        if (ClosedCells == pole->GetHeight() * pole->GetWidth()) {
            if (!pole->DeleteMine(x, y))return;
        }
        else {
            pole->fail(x, y);
            losing(0);
            return;
        }
    }
    int openCount = pole->Open(x, y, &countOfMarkes);
    if (openCount != 0)isGameRun = true;
    ClosedCells -= openCount;
    if (ClosedCells == pole->GetMinesCount())win();
}

int Game::GetLevel() {
    return level;
}

int Game::getHeight(){
    return pole->GetHeight();
}

int Game::getWidth(){
    return pole->GetWidth();
}

int Game::getMines(){
    return pole->GetMinesCount();
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

bool Game::AutoSolve() {
    int count = pole->AutoMark();
    this->countOfMarkes -= count;
    if (count == 0) {
        count = pole->AutoOpen(&countOfMarkes);
        this->ClosedCells -= count;
    }
    if (count == 0) {
        count = pole->Guess(&countOfMarkes);
        this->ClosedCells -= count;
    }
    if (count == -1)return 0;
    return 1;
}

void Game::IsMarkTrue() {
    countOfMarkes += pole->IsMarkTrue();
}

void Game::win(){
    solved = true;
    isGameRun = false;
    pole->win();
    countOfMarkes = 0;
}

void Game::losing(int reason){
    isGameRun = false;
    lose = true;
}

bool Game::GetIsGameRun(){
    return isGameRun;
}

bool Game::stop() {
    if (solved || lose)return true;
    else return false;
}

