#pragma once
#include "Header.h"

using namespace sf;

class Interface : public Drawable, public Transformable {
	Texture DDMenuIm;
	Texture subMenuIm;
	Texture CountersIm;
	bool isDDMenu;
public:
	Interface();
	virtual void draw(RenderTarget& target, RenderStates states)const;
};

