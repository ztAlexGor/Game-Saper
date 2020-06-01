#include "Interface.h"

Interface::Interface(){
	subMenuIm.loadFromFile("Images/subMenu.Gif");
	CountersIm.loadFromFile("Images/Counters.Gif");
    RestartIm.loadFromFile("Images/Restart.png");
    subMenuStatus = 0;
    subMenuStatus = 0;
    isDDMenu = false;
}

void Interface::draw(RenderTarget& target, RenderStates states) const{
    Sprite subMenu;
    subMenu.setTexture(subMenuIm);
    subMenu.setTextureRect(sf::IntRect(0, subMenuStatus * 25, 98, 25));
    if (isDDMenu)subMenu.setTextureRect(sf::IntRect(0, 25, 98, 25));
    //subMenu.setPosition(0, 0);

    RectangleShape lineMenu(Vector2f(target.getSize().x, 25));
    lineMenu.setFillColor(Color(240, 240, 240));

    RectangleShape underMenuLine(Vector2f(target.getSize().x, 1));
    underMenuLine.setFillColor(Color(172, 168, 153));
    underMenuLine.setPosition(0, 25);

    RectangleShape fon(Vector2f(target.getSize().x, target.getSize().y));
    fon.setFillColor(Color(240, 240, 240));

    Sprite Counters;
    Counters.setTexture(CountersIm);
    Counters.setPosition(20, 31);
    Counters.setTextureRect(IntRect(0, 0, 80, 33));

    Sprite Restart;
    Restart.setTexture(RestartIm);
    Restart.setPosition(target.getSize().x / 2 - 16, 31);
    Restart.setTextureRect(IntRect(0, 0, 33, 33));


    target.draw(fon);
    target.draw(lineMenu);
    target.draw(Counters);
    Counters.setTextureRect(IntRect(80, 0, 80, 33));
    Counters.setPosition(target.getSize().x - 100, 31);
    target.draw(Counters);
    target.draw(Restart);
    target.draw(subMenu);
    target.draw(underMenuLine);
    underMenuLine.setPosition(0, 71);
    target.draw(underMenuLine);
}

void Interface::setSubMenuStatus(int x, int y){
    if (y >= 0 && y <= 25) {
        if (x >= 0 && x <= 41)subMenuStatus = 1;
        else if (x >= 42 && x <= 98)subMenuStatus = 2;
        else subMenuStatus = 0;
    }else subMenuStatus = 0;
}

void Interface::setIsDDMenu(bool arg){
    isDDMenu = arg;
}
