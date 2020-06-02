#include "TextBox.h"

string checkInput(string);

TextBox::TextBox(){
	size = Vector2f(90, 16);
	length = 0;
	isActive = false;
	font.loadFromFile("Fonts/Calibri.ttf");
	input_text.setFont(font);
	input_text.setFillColor(Color::Black);
	input_text.setCharacterSize(12);
	input_text.setLetterSpacing(2.5);

	default_text.setFont(font);
	default_text.setFillColor(Color(160, 160, 160));
	default_text.setCharacterSize(12);
	default_text.setLetterSpacing(2.5);

}

bool TextBox::getIsActive(){
	return isActive;
}

bool TextBox::input(Event event, string (*getCorrectInput)(int, int, int), int x, int y) {
	if (event.type == Event::MouseButtonReleased) {
		Vector2f Mpos(event.mouseButton.x, event.mouseButton.y);
		if (Mpos.x >= position.x && Mpos.x <= position.x + size.x && Mpos.y >= position.y && Mpos.y <= position.y + size.y) {
			isActive = true;
		}
		else {
			isActive = false;
			if (this->getNumber() != 0)input_text.setString(getCorrectInput(this->getNumber(), x, y));
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

		str = checkInput(str);

		if (str != "0000") {
			input_text.setString(str);
			length++;
			return true;
		}
	}
	return false;
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
	if (input_text.getString() != "0" && input_text.getString() != "")target.draw(input_text);
	else target.draw(default_text);
}

int TextBox::getNumber(){
	int num = 0;
	string s = input_text.getString();
	for (int i = 0; i < s.size(); i++) {
		num *= 10;
		num += (int)s[i] - 48;
	}
	return num;
}

void TextBox::setPosition(Vector2f pos){
	position = pos;
	input_text.setPosition(position + Vector2f(10, 1));
	default_text.setPosition(position + Vector2f(10, 1));
}

void TextBox::setDefaulText(string s){
	default_text.setString(s);
}

string TextBox::getDefaulText() {
	return default_text.getString();
}

void TextBox::setSize(Vector2f size){
	this->size = size;
}

Vector2f TextBox::getSize(){
	return size;
}

string checkInput(string s) {
	if (s.size() > 3)return "0000";
	for (int i = 0; i < s.size(); i++) {
		if ((int)s[i] < 48 || (int)s[i]>57)return "0000";
	}
	int num = 0;
	for (int i = 0; i < s.size(); i++) {
		num *= 10;
		num += (int)s[i] - 48;
	}
	return to_string(num);
}