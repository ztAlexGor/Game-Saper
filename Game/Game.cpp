#include "Game.h"

Game::Game(int level): level(level){
	if (level == 1) {
		pole = new Field{ 10, 8, 10 };//Easy level
	}
	else if (level == 2) {
		pole = new Field{ 13, 20, 40 };//Medium level
	}
	else if (level == 3) {
		pole = new Field{ 33, 20, 100 };//Hard level
	}

	/*else if (level == 4) {
		pole = new Field{ ,  , };//Hard level
	}*/
}

void Game::draw(RenderTarget& target, RenderStates states) const{
	states.transform *= getTransform();
	Color color = Color(200, 100, 200);

	// ������ ����� �������� ����
	RectangleShape shape(Vector2f(pole->GetHeight() * 20 + 20.f, pole->GetWidth() * 20 + 20.f));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(Color::Transparent);
	target.draw(shape, states);

	// �������������� ����� ��� ��������� ���� ������
	shape.setSize(sf::Vector2f(Cell::size - 2, Cell::size - 2));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);

	// �������������� ��������� ��������� ��� ��������� ������� ������
	Text text;// ("", font, 52);

	for (unsigned int i = 0; i < pole->GetHeight(); i++){
		for (unsigned int j = 0; j < pole->GetWidth(); j++) {
			shape.setOutlineColor(color);
			//text.setFillColor(color);
			//text.setString(std::to_string());
			if (pole->GetCellStatus(i, j) == 1)
			{
				// �������� ����������� �������� ������ ������
				shape.setOutlineColor(Color::Cyan);
				text.setFillColor(Color::Cyan);
			}
			else if (pole->GetCellStatus(i, j) == 0)
			{
				// ������ ������ �� ����� ������ �������� ������
				text.setFillColor(Color::Green);
				shape.setOutlineColor(Color::Green);
			}

			
			// ���������� ������� ������ ��� ���������
			Vector2f position(i * Cell::size + 10.f, j * Cell::size + 10.f);
			shape.setPosition(position);
			// ������� ������ �������� �������
			//text.setPosition(position.x + 30.f + (elements[i] < 10 ? 15.f : 0.f), position.y + 25.f);
			target.draw(shape, states);
			target.draw(text, states);
		}
	}
}
