#include "Header.h"

using namespace std;

int Menu(RenderWindow& window, Game& game);
int processingResult(RenderWindow& window, Game& game, int res);
int mousePosition(int, int);
string getCorrectInputOfHeight(int, int, int);
string getCorrectInputOfWidth(int, int, int);
string getCorrectInputOfMines(int, int, int);

int main()
{
    FreeConsole();
    RenderWindow window(VideoMode(10 * Cell::size + 20, 8 * Cell::size + 90), "MineSweeper", Style::Close);
    window.setKeyRepeatEnabled(false);

    Font font;
    font.loadFromFile("Fonts/Calibri.ttf");

    Game game = Game(1);
    Interface interf;
    DownDropMenu DDMenu;

    Clock gameTimeClock;
    int gameTime = 0;
    int timeInMenu = 0;
    int lastTime = 0;

    bool isAutoSolve = 0;
    //Menu(window, game);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == event.KeyReleased) {
                if (event.key.code == Keyboard::F1) {
                    int currTime = gameTimeClock.getElapsedTime().asSeconds();
                    if (Menu(window, game)) {
                        gameTimeClock.restart();
                        gameTime = 0;
                        timeInMenu = 0;
                        isAutoSolve = 0;
                        lastTime = 0;
                    }else timeInMenu += gameTimeClock.getElapsedTime().asSeconds() - currTime;
                }
                else if (event.key.code == Keyboard::Escape) {
                    window.close();
                }
            }
            else if (event.type == event.MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (event.key.code == Mouse::Left ) {
                    if (!game.stop() && !DDMenu.getDDMenuStatus() && !isAutoSolve) {
                        if (mousePos.x >= 10 && mousePos.y >= 81) {
                            int px = (mousePos.x - 10) / Cell::size;
                            int py = (mousePos.y - 81) / Cell::size;
                            game.OpenCell(py, px);
                        }
                    }
                    DDMenu.setDDMenuStatus(mousePos.x, mousePos.y);
                    int res = DDMenu.selectOption(mousePos.x, mousePos.y);
                    int currTime = gameTimeClock.getElapsedTime().asSeconds();
                    res = processingResult(window, game, res);
                    if (mousePos.x > window.getSize().x / 2 - 12 && mousePos.x < window.getSize().x / 2 + 13 && mousePos.y > 36 && mousePos.y < 61)res = processingResult(window, game, 1);
                    if (res == 1) {//if new game
                        gameTimeClock.restart();
                        gameTime = 0;
                        timeInMenu = 0;
                        isAutoSolve = 0;
                        lastTime = 0;
                    }
                    else if (res == 2) {//start auto resolve
                        timeInMenu += gameTimeClock.getElapsedTime().asSeconds() - currTime;
                        if (!isAutoSolve) {
                            isAutoSolve = true;
                            game.IsMarkTrue();
                        }
                    }
                    else timeInMenu += gameTimeClock.getElapsedTime().asSeconds() - currTime;
                }
                else if (event.key.code == Mouse::Right && !game.stop() && !DDMenu.getDDMenuStatus() && !isAutoSolve) {
                    if (mousePos.x >= 10 && mousePos.y >= 81) {
                        int px = (mousePos.x - 10) / Cell::size;
                        int py = (mousePos.y - 81) / Cell::size;
                        game.SetSelfStatus(py, px);
                    }
                }
            }

            interf.setSubMenuStatus(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
            interf.setIsDDMenu(DDMenu.getDDMenuStatus());
            if (DDMenu.getDDMenuStatus())DDMenu.setDDMenuStatus(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
        }
        
        if (isAutoSolve) {//Auto solve
            int currTime = gameTimeClock.getElapsedTime().asSeconds();
            if (currTime > lastTime) {
                if (!game.AutoSolve()) {
                    isAutoSolve = 0;
                    game.win();
                }
                lastTime = currTime;
            }
        }

        if (game.GetIsGameRun() && !isAutoSolve) {//time calculating
            gameTime = gameTimeClock.getElapsedTime().asSeconds() - timeInMenu;
            if (gameTime > 998)game.losing(2);
            else if (gameTime < 0)gameTime = 0;
        }
        else if(!isAutoSolve)gameTimeClock.restart();

        Text timeInGame(to_string(999 - gameTime), font, 18);
        timeInGame.setStyle(Text::Bold);
        timeInGame.setFillColor(Color::Red);
        timeInGame.setPosition(Vector2f(window.getSize().x - 55, 36));
        


        window.clear();
        window.draw(interf);
        window.draw(timeInGame);
        window.draw(game);
        window.draw(DDMenu);
        window.display();
    }

    return 0;
}

int Menu(RenderWindow& window, Game& game) {//0 - nothing have changed, 1 - level has changed
    Vector2u WinSize = window.getSize();

    RectangleShape shape(Vector2f(WinSize.x, WinSize.y));
    shape.setFillColor(Color(240, 240, 240));

    Texture SettingsIm;
    SettingsIm.loadFromFile("Images/Settings.png");
    Sprite Settings;
    Settings.setTexture(SettingsIm);
    Settings.setPosition(Vector2f(WinSize.x / 2 - 134, WinSize.y / 2 - 145));

    Texture OKIm;
    OKIm.loadFromFile("Images/OK.png");
    Sprite OK;
    OK.setTexture(OKIm);
    OK.setPosition(Vector2f(WinSize.x / 2 + 35, WinSize.y / 2 + 115));

    Texture CancelIm;
    CancelIm.loadFromFile("Images/Cancel.png");
    Sprite Cancel;
    Cancel.setTexture(CancelIm);
    Cancel.setPosition(Vector2f(WinSize.x / 2 - 134, WinSize.y / 2 + 115));

    Texture FlagIm;
    FlagIm.loadFromFile("Images/Flag.png");
    Sprite Flag;
    Flag.setTexture(FlagIm);

    Font font;
    font.loadFromFile("Fonts/Calibri.ttf");
    Color TextColor(Color::Red);


    TextBox widthInp;
    widthInp.setPosition(Vector2f(WinSize.x / 2 - 20, WinSize.y / 2 + 26));
    widthInp.setDefaulText("20");

    TextBox heightInp;
    heightInp.setPosition(Vector2f(WinSize.x / 2 - 20, WinSize.y / 2 + 47));
    heightInp.setDefaulText("15");

    TextBox minesInp;
    minesInp.setPosition(Vector2f(WinSize.x / 2 - 20, WinSize.y / 2 + 68));
    minesInp.setDefaulText("50");
    
    
    
    ////text Exit
    //Text textExit(L"бшунд", font, 30);
    //textExit.setStyle(Text::Bold);
    //textExit.setOrigin(textExit.getLocalBounds().width / 2, textExit.getLocalBounds().height / 2);
    //textExit.setPosition(Vector2f(WinSize.x / 2, WinSize.y / 2 + 50));

    bool isOK , isCancel;
    int selectLevel = 0;//0 - not level select, 1 - select type of level, custome level options
    int isFlag;//0 - if it's not

    while (window.isOpen()){
        isOK = isCancel = isFlag = 0;
        Event event;

        Vector2i localPosition = sf::Mouse::getPosition(window);
        int mPos = mousePosition(localPosition.x - WinSize.x / 2, localPosition.y - WinSize.y / 2);

        while (window.pollEvent(event)){

            if (event.type == Event::Closed)
                window.close();
            else if (event.type == event.MouseButtonPressed) {//click left button
                if (event.key.code == Mouse::Left) {
                    

                    if (mPos == 1) {//easy
                        if (selectLevel == 1)selectLevel = 0;
                        else selectLevel = 1;
                    }
                    else if (mPos == 2) {//medium
                        if (selectLevel == 2)selectLevel = 0;
                        else selectLevel = 2;
                    }
                    else if (mPos == 3) {//hard
                        if (selectLevel == 3)selectLevel = 0;
                        else selectLevel = 3;
                    }
                    else if (mPos == 4) {//custome
                        if (selectLevel == 4)selectLevel = 0;
                        else selectLevel = 4;
                    }
                    else if (mPos == 5) {//OK
                        if (selectLevel == 0);
                        else if (selectLevel == 1) {
                            if (game.GetLevel() != 1)window.create(VideoMode(10 * Cell::size + 20, 8 * Cell::size + 90), "MineSweeper", Style::Close);
                            game.newGame(1);
                            return 1;
                        }
                        else if (selectLevel == 2) {
                            if (game.GetLevel() != 2)window.create(VideoMode(20 * Cell::size + 20, 13 * Cell::size + 90), "MineSweeper", Style::Close);
                            game.newGame(2);
                            return 1;
                        }
                        else if (selectLevel == 3) {
                            if (game.GetLevel() != 3)window.create(VideoMode(33 * Cell::size + 20, 20 * Cell::size + 90), "MineSweeper", Style::Close);
                            game.newGame(3);
                            return 1;
                        }
                        else if (selectLevel == 4) {
                            if (widthInp.getNumber() == 0 || heightInp.getNumber() == 0 || minesInp.getNumber() == 0);
                            else {
                                window.create(VideoMode(widthInp.getNumber() * Cell::size + 20, heightInp.getNumber() * Cell::size + 90), "MineSweeper", Style::Close);//edit this
                                game.newGame(widthInp.getNumber(), heightInp.getNumber(), minesInp.getNumber());
                                return 1;
                            }
                        }
                    }
                    else if (mPos == 6) {//Cancel
                        return 0;
                    }
                }
            }
            if (event.type == event.KeyReleased) {
                if (event.key.code == Keyboard::F2) {
                    if (game.GetLevel() != 1)window.create(VideoMode(10 * Cell::size + 20, 8 * Cell::size + 90), "MineSweeper", Style::Close);//254 + 15, 290
                    game.newGame(1);
                    return 1;
                }
                else if (event.key.code == Keyboard::F3) {
                    if (game.GetLevel() != 2)window.create(VideoMode(20 * Cell::size + 20, 13 * Cell::size + 90), "MineSweeper", Style::Close);
                    game.newGame(2);
                    return 1;
                }
                else if (event.key.code == Keyboard::F4) {
                    if (game.GetLevel() != 3)window.create(VideoMode(33 * Cell::size + 20, 20 * Cell::size + 90), "MineSweeper", Style::Close);
                    game.newGame(3);
                    return 1;
                }
            }

            if (heightInp.input(event, getCorrectInputOfHeight, WinSize.x, WinSize.y))selectLevel = 4;
            if (widthInp.input(event, getCorrectInputOfWidth, WinSize.x, WinSize.y))selectLevel = 4;
            if (minesInp.input(event, getCorrectInputOfMines, widthInp.getNumber(), heightInp.getNumber()))selectLevel = 4;
        }
        if (selectLevel == 1 || (mPos == 1 && selectLevel == 0)) {//easy
            isFlag = 1;
            Flag.setPosition(Vector2f(WinSize.x / 2 - 118, WinSize.y / 2 - 94));//16 51
        }
        else if (selectLevel == 2 || (mPos == 2 && selectLevel == 0)) {//medium
            isFlag = 1;
            Flag.setPosition(Vector2f(WinSize.x / 2 + 13, WinSize.y / 2 - 94));//147 51
        }
        else if (selectLevel == 3 || (mPos == 3 && selectLevel == 0)) {//hard
            isFlag = 1;
            Flag.setPosition(Vector2f(WinSize.x / 2 - 53, WinSize.y / 2 - 48));//81 97
        }
        else if (selectLevel == 4 || (mPos == 4 && selectLevel == 0)) {//custome level
            isFlag = 1;
            Flag.setPosition(Vector2f(WinSize.x / 2 - 118, WinSize.y / 2 + 6));//16 151
        }

        if (mPos == 5) {//OK
            isOK = 1;
        }
        else if (mPos == 6) {//Cancel
            isCancel = 1;
        }
        

        window.draw(shape);
        window.draw(Settings);
        window.draw(heightInp);
        window.draw(widthInp);
        window.draw(minesInp);
        if (isOK)window.draw(OK);
        else if (isCancel)window.draw(Cancel);
        if (isFlag)window.draw(Flag);
        window.display();
    }
}

int processingResult(RenderWindow& window, Game& game, int res){
    if (res == 0) {
        return 0;
    }
    else if (res == 1) {
        game.newGame(game.getWidth(), game.getHeight(), game.getMines());
        return 1;
    }
    else if (res == 2) {//Open Cell Algorithm
        return 2;
    }
    else if (res == 3) {
        if (game.GetLevel() != 1)window.create(VideoMode(10 * Cell::size + 20, 8 * Cell::size + 90), "MineSweeper", Style::Close);
        game.newGame(1);
        return 1;
    }
    else if (res == 4) {
        if (game.GetLevel() != 2)window.create(VideoMode(20 * Cell::size + 20, 13 * Cell::size + 90), "MineSweeper", Style::Close);
        game.newGame(2);
        return 1;
    }
    else if (res == 5) {
        if (game.GetLevel() != 3)window.create(VideoMode(33 * Cell::size + 20, 20 * Cell::size + 90), "MineSweeper", Style::Close);
        game.newGame(3);
        return 1;
    }
    else if (res == 6) {
        return Menu(window, game);
    }
    else if (res == 7) {
        return Menu(window, game);
    }
    else if (res == 8) {
        window.close();
        return 0;
    }

}

int mousePosition(int x, int y) {
    x += 134;
    y += 145;




    if (x >=12 && x <= 101 && y>=44 && y <=72) {//easy
        return 1;
    }
    else if (x >= 143 && x <= 240 && y >= 44 && y <= 72) {//medium
        return 2;
    }
    else if (x >= 77 && x <= 182 && y >= 89 && y <= 117) {//hard
        return 3;
    }
    else if (x >= 13 && x <= 79 && y >= 149 && y <= 169) {//custome
        return 4;
    }
    else if (x >= 178 && x <= 237 && y >= 262 && y <= 280) {//OK
        return 5;
    }
    else if (x >= 32 && x <= 91 && y > 262 && y < 280) {//Cancel
        return 6;
    }
    return 0;
}

string getCorrectInputOfHeight(int num, int x, int y) {
    if (num > 30 && num > VideoMode::getDesktopMode().height / 25 - 15)num = min(30, num = VideoMode::getDesktopMode().height / 25 - 10);
    if (num < 8)num = 8;
    return to_string(num);
}

string getCorrectInputOfWidth(int num, int x, int y) {
    if (num > 50 && num > VideoMode::getDesktopMode().width / 25 - 15)num = min(50, num = VideoMode::getDesktopMode().width / 25 - 10);
    if (num < 10)num = 10;
    return to_string(num);
}

string getCorrectInputOfMines(int num, int x, int y) {
    if (num < 1)num = 1;
    else if (num > x*y - 1)num = x * y - 1;
    if (num < 0)num = 0;
    return to_string(num);
}   