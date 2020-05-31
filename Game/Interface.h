#pragma once
#include "Header.h"
#include <SFML\Graphics\Color.hpp>

using namespace sf;

class Interface : public Drawable, public Transformable {
	Texture subMenuIm;
	Texture CountersIm;
	Texture SmileIm;
	int subMenuStatus;//0 - not active; 1 - active, 2 - 8 sprite activate
	bool isDDMenu;
public:
	Interface();
	virtual void draw(RenderTarget& target, RenderStates states)const;
	void setSubMenuStatus(int x, int y);
	void setIsDDMenu(bool arg);
};

