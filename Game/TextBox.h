#pragma once
#include "Header.h"

using namespace sf;
using namespace std;

class TextBox : public Drawable, public Transformable {
	Font font;
	int length;
	Text input_text;
	bool isActive;
	Vector2f position;
	Vector2f size;
public:
	TextBox();
	bool getIsActive();
	void input(Event event);
	void draw(RenderTarget& target, RenderStates states)const;
	string getText();
	void setPosition(Vector2f pos);
	void setSize(Vector2f size);
	Vector2f getSize();
};
