#include "Game.h"

Game::Game(int level): level(level){//constructor
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

	/*else if (level == 4) {
		pole = new Field{ ,  , };//Custome level
	}*/
}

void Game::newGame(int level){
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
}

//Game::Game(const Game& other){//copy constructor
//	this->level = other.level;
//	this->solved = other.solved;
//	if (level == 1) {
//		pole = new Field{ 10, 8, 10 };//Easy level
//	}
//	else if (level == 2) {
//		pole = new Field{ 13, 20, 40 };//Medium level
//	}
//	else if (level == 3) {
//		pole = new Field{ 33, 20, 100 };//Hard level
//	}
//}

void Game::draw(RenderTarget& target, RenderStates states) const{
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

	Texture Texture;
	Texture.loadFromFile("Images/Cell.png");
	Sprite Cell;
	Cell.setTexture(Texture);

	for (unsigned int i = 0; i < pole->GetHeight(); i++){
		for (unsigned int j = 0; j < pole->GetWidth(); j++){
			text.setString("");
			if (pole->GetCellStatus(i, j) == 0){// Не открытая клеточка
				Cell.setTextureRect(sf::IntRect(0, 0, 25, 25));
				text.setFillColor(color);
				int count = pole->GetCellNumber(i, j);
				if (count == 9) {
					text.setFillColor(Color::Black);
					text.setString(std::to_string(count));
				}
				else if (count == 0)text.setString("");
				else text.setString(std::to_string(count));
			}
			else if (pole->GetCellStatus(i, j) == 1){//Уже открытая клеточка
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
				Cell.setTextureRect(sf::IntRect(12, 0, 25, 25));
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

void Game::OpenCell(int x, int y){
	pole->Open(x, y);
}

int Game::GetLevel(){
	return level;
}

Game::~Game(){
	delete pole;
}
