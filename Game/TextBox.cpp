#include "TextBox.h"



TextBox::TextBox(){
	size = Vector2f(90, 16);
	length = 0;
	isActive = false;
	font.loadFromFile("Fonts/Calibri.ttf");
	input_text.setFont(font);
	input_text.setFillColor(Color::Black);
	input_text.setCharacterSize(12);
	input_text.setLetterSpacing(2.5);
}

bool TextBox::getIsActive(){
	return isActive;
}

void TextBox::input(Event event){
	if (event.type == Event::MouseButtonReleased) {
		Vector2f Mpos(event.mouseButton.x, event.mouseButton.y);
		if (Mpos.x >= position.x && Mpos.x <= position.x + size.x && Mpos.y >= position.y && Mpos.y <= position.y + size.y) {
			isActive = true;
		}
		else {
			isActive = false;
		}
	}

	if (event.type == Event::TextEntered && isActive) {
		String str = input_text.getString();

		if (event.text.unicode == 8) {//backspace
			if (str.getSize() > 0) {
				length--;
				str = str.substring(0, str.getSize() - 1);
			}
		}
		else if (event.text.unicode == 27) {//enter
			isActive = false;
		}
		else {
			String sfstr = "";
			sfstr += event.text.unicode;
			str += sfstr.toAnsiString();
		}

		if (str.getSize() == 6) return;

		input_text.setString(str);
		length++;
	}
}

void TextBox::draw(RenderTarget& target, RenderStates states)const {
	RectangleShape box;
	box.setSize(size);
	box.setFillColor(sf::Color::White);
	box.setOutlineThickness(1);
	box.setPosition(position);
	if (isActive)box.setOutlineColor(sf::Color::Red);
	else box.setOutlineColor(sf::Color::White);

	target.draw(box);
	target.draw(input_text);
}

string TextBox::getText(){
	return input_text.getString();
}

void TextBox::setPosition(Vector2f pos){
	position = pos;
	input_text.setPosition(position + Vector2f(10, 1));
}

void TextBox::setSize(Vector2f size){
	this->size = size;
}

Vector2f TextBox::getSize(){
	return size;
}
