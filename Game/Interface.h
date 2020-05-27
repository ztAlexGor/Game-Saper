#pragma once
#include "Header.h"

using namespace sf;

class Interface : public Drawable, public Transformable {
	Texture subMenuIm;
	Texture CountersIm;
	int subMenuStatus;//0 - not active; 1 - active, 2 - 8 sprite activate
public:
	Interface();
	virtual void draw(RenderTarget& target, RenderStates states)const;
	void setSubMenuStatus(int x, int y);
};

