#include "DownDropMenu.h"

DownDropMenu::DownDropMenu(){
	DDMenuIm.loadFromFile("Images/DDMenu.png");
	DDMenuStatus = 0;
}

int DownDropMenu::selectOption(int x, int y){
	if (DDMenuStatus == 0) {
		return 0;
	}
	else {
		if (x >= 0 && x <= 193) {
			if (y >= 23 && y <= 49) {//26
				DDMenuStatus = 0;
				return 1;
			}
			else if (y >= 50 && y <= 76) {//26 
				DDMenuStatus = 0;
				return 2;
			}
			else if (y >= 77 && y <= 100) {//23
				DDMenuStatus = 0;
				return 3;
			}
			else if (y >= 101 && y <= 120) {//19
				DDMenuStatus = 0;
				return 4;
			}
			else if (y >= 121 && y <= 140) {//19
				DDMenuStatus = 0;
				return 5;
			}
			else if (y >= 141 && y <= 162) {//21
				DDMenuStatus = 0;
				return 6;
			}
			else if (y >= 165 && y <= 189) {//24
				DDMenuStatus = 0;
				return 7;
			}
			else if (y >= 191 && y <= 216) {//25 
				DDMenuStatus = 0;
				return 8;
			}
		}
	}
	return 0;
}

void DownDropMenu::setDDMenuStatus(int x, int y){//193 195
	if (DDMenuStatus == 0) {
		if (y >= 0 && y <= 25 && x >= 0 && x <= 41)DDMenuStatus = 1;
	}
	else {
		 //if (y >= 0 && y <= 25 && x >= 0 && x <= 41)DDMenuStatus = 0;
		if (x >= 0 && x <= 193) {
			if (y >= 23 && y <= 49) {//26
				DDMenuStatus = 2;
			}
			else if (y >= 50 && y <= 76) {//26 
				DDMenuStatus = 3;
			}
			else if (y >= 77 && y <= 100) {//23
				DDMenuStatus = 4;
			}
			else if (y >= 101 && y <= 120) {//19
				DDMenuStatus = 5;
			}
			else if (y >= 121 && y <= 140) {//19
				DDMenuStatus = 6;
			}
			else if (y >= 141 && y <= 162) {//21
				DDMenuStatus = 7;
			}
			else if (y >= 165 && y <= 187) {//24
				DDMenuStatus = 8;
			}
			else DDMenuStatus = 1;
		}
		else DDMenuStatus = 0;
	}
}

bool DownDropMenu::getDDMenuStatus(){
	if (DDMenuStatus == 0)return false;
	else return true;
}

void DownDropMenu::draw(RenderTarget& target, RenderStates states) const{

	Sprite DDMenu;//Drop down menu
	DDMenu.setTexture(DDMenuIm);
	DDMenu.setPosition(1, 23);

	if (DDMenuStatus) {
		DDMenu.setTextureRect(IntRect((DDMenuStatus - 1) * 193, 0, 193, 168));
		target.draw(DDMenu);
	}
}