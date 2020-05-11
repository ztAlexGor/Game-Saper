#include "Header.h"

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(274, 224), "MineSweeper", Style::Close);
    /*CircleShape shape(200.f);
    shape.setFillColor(Color::Magenta);*/

    Game game = Game(1);
    game.setPosition(2.f, 2.f);

    Clock clock;
    float time;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (event.type == event.KeyReleased) {
            if (event.key.code == Keyboard::F2) {
                window.create(VideoMode(274, 224), "MineSweeper", Style::Close);
                game.newGame(1);
            }
            else if (event.key.code == Keyboard::F3) {
                window.create(VideoMode(349, 524), "MineSweeper", Style::Close);
                game.newGame(2);
            }
            else if (event.key.code == Keyboard::F4) {
                window.create(VideoMode(849, 524), "MineSweeper", Style::Close);
                game.newGame(3);
            }
        }

        /*if (Keyboard::isKeyPressed(Keyboard::Key::F2)) {
            window.setSize(Vector2u(274, 224));
            game.newGame(1);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::F3)) {
            window.setSize(Vector2u(500, 500));
            game.newGame(2);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::F4)) {
            window.setSize(Vector2u(800, 800));
            game.newGame(3);
        }*/

        window.clear();
        window.draw(game);
        window.display();
    }

    return 0;
}