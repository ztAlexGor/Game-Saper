#include "Interface.h"

Interface::Interface(){
	subMenuIm.loadFromFile("Images/subMenu.Gif");
	DDMenuIm.loadFromFile("Images/DDMenu.png");
	CountersIm.loadFromFile("Images/Counters.Gif");
    isDDMenu = false;
}

void Interface::draw(RenderTarget& target, RenderStates states) const{
    Sprite subMenu;
    subMenu.setTexture(subMenuIm);
    subMenu.setTextureRect(sf::IntRect(0, 0, 98, 25));
    //subMenu.setPosition(0, 0);

    Sprite DDMenu;//Drop down menu
    DDMenu.setTexture(DDMenuIm);
    DDMenu.setPosition(10, 25);

    RectangleShape lineMenu(Vector2f(target.getSize().x, 25));
    lineMenu.setFillColor(Color(240, 240, 240));

    RectangleShape underMenuLine(Vector2f(target.getSize().x, 1));
    underMenuLine.setFillColor(Color(172, 168, 153));
    underMenuLine.setPosition(0, 25);

    RectangleShape fon(Vector2f(target.getSize().x, target.getSize().y));
    fon.setFillColor(Color(240, 240, 240));

    Sprite Counters;
    Counters.setTexture(CountersIm);
    Counters.setPosition(31, 25);


    lineMenu.setSize(Vector2f(target.getSize().x, 25));
    fon.setSize(Vector2f(target.getSize().x, target.getSize().y));
    underMenuLine.setPosition(0, 25);
    underMenuLine.setSize(Vector2f(target.getSize().x, 1));
    Counters.setTextureRect(sf::IntRect(0, 0, 80, 33));
    Counters.setPosition(25, 31);

    target.draw(fon);
    target.draw(subMenu);
    target.draw(Counters);
    Counters.setTextureRect(sf::IntRect(80, 0, 80, 33));
    Counters.setPosition(target.getSize().x - 90, 31);
    target.draw(Counters);
    target.draw(lineMenu);
    target.draw(underMenuLine);
    underMenuLine.setPosition(0, 71);
    target.draw(underMenuLine);

    if (isDDMenu) {
        target.draw(DDMenu);
    }
}
