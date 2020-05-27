#pragma once
#include "Header.h"

using namespace sf;

class DownDropMenu : public Drawable, public Transformable {
	Texture DDMenuIm;
	int DDMenuStatus;//0 - not active; 1 - active, 2 - 8 sprite activate
public:
	DownDropMenu();
	int selectOption(int x, int y);
	void setDDMenuStatus(int x, int y);
	bool getDDMenuStatus();
	virtual void draw(RenderTarget& target, RenderStates states)const;
};

