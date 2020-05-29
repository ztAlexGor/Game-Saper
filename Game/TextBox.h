#pragma once
#include "Header.h"

using namespace sf;
using namespace std;

class TextBox : public Drawable, public Transformable {
	Font font;
	int length;
	Text input_text;
	Text default_text;
	bool isActive;
	Vector2f position;
	Vector2f size;
public:
	TextBox();
	bool getIsActive();
	bool input(Event event, string(*func)(int, int, int), int, int);
	void draw(RenderTarget& target, RenderStates states)const;
	int getNumber();
	void setPosition(Vector2f pos);
	void setDefaulText(string s);
	void setSize(Vector2f size);
	Vector2f getSize();
};
