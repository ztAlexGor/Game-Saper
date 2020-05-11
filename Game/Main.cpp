#include "Header.h"

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(500, 400), "MineSweeper");
    /*CircleShape shape(200.f);
    shape.setFillColor(Color::Magenta);*/

    Game game(1);
    game.setPosition(50.f, 50.f);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(game);
        window.display();
    }

    return 0;
}
//33*20