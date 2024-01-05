#include <SFML/Graphics.hpp>
#include<time.h>
#include <SFML/Audio.hpp>
#include<iostream>
#include<fstream>
using namespace std; 
using namespace sf;
const char title2[] = "Menu Screen";
string playersName[2]; // Array to store two names
template<class T, class U>
class Menu
{

public:

Sprite background; //Game background sprite
Texture bg_texture;
Music music, startmusic, quitmusic;
bool musicflag_bg = 0;

Menu()
{
    bg_texture.loadFromFile("asserts/mainmenu.png");
    background.setTexture(bg_texture);
    if (!music.openFromFile("asserts/bgmusic.wav"))
    {
        std::cout << "Failed to load menu music!" << std::endl;
    }
    music.setVolume(50);
    startmusic.setVolume(50);
    quitmusic.setVolume(50);
    startmusic.openFromFile("asserts/start.wav");
    quitmusic.openFromFile("asserts/start.wav");
    //background.setScale(2.15, 1.5);
}
bool getMusicFlag()
{
    return musicflag_bg;
}
void names_menu()
{   
    for (int i = 0; i < 2; i++)
        playersName[i] = "";
    Font font;
    font.loadFromFile("font2.ttf");

    bool filesaved = 0;
    Text enterNameText;
    enterNameText.setFont(font);
    enterNameText.setCharacterSize(50);
    Text nameText[2];   // Array of Text objects for displaying names
    for (int i = 0; i < 2; ++i) {
        nameText[i].setFont(font);
        nameText[i].setCharacterSize(70);
        nameText[i].setFillColor(Color::White);
        nameText[i].setPosition(180 + i *700, 525); // Adjust the position for each name
    }

    Sprite sprite;
    Texture texture;
    if (!texture.loadFromFile("asserts/names.png"))
        cout << "Not Found assets/names.png";
    sprite.setTexture(texture);
    RenderWindow window(VideoMode(1280, 720), "Enter Name "); // Replace "Your Window Title" with the desired title

    srand(time(0));
    bool enteringBoard = true;
    sf::Event event;

    int activeName = 0; // To keep track of which name is currently being entered

    while (enteringBoard && window.isOpen())
    {
        window.clear();
        enterNameText.setString("Enter Name " + to_string(activeName + 1) + ":");
        nameText[0].setString(playersName[0]);
        nameText[1].setString(playersName[1]);

        window.draw(sprite);
        window.draw(enterNameText);
        window.draw(nameText[0]);
        window.draw(nameText[1]);
        window.display();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                enteringBoard = false;
            }
            else if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    if (event.text.unicode == '\b' && !playersName[activeName].empty())
                    {
                        // Handle backspace
                        playersName[activeName].pop_back();
                    }
                    else if (event.text.unicode == '\r' || event.text.unicode == '\n')
                    {
                        // Handle enter key
                        if (activeName < 1)
                            activeName++; // Switch to the next name
                        else
                            enteringBoard = false; // Both names entered, exit the loop
                    }
                    else
                    {
                        // Add the entered character to the name string
                        playersName[activeName] += static_cast<char>(event.text.unicode);
                    }
                }
            }
        }
    }
    for (string player : playersName)
        cout << "name : " << player;
}

bool display_menu()

{

    Font font;
    font.loadFromFile("font2.ttf");

    music.play();


    srand(time(0));

    RenderWindow window(VideoMode(1280, 720), title2);
    while (window.isOpen())
        {
           	Event e;
           	while (window.pollEvent(e))
           	{ 
                if (e.type == Event::Closed)
                    //window.close();  
                    exit(11);
                else if (e.key.code == Keyboard::Escape)
                    exit(11);

                if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)
                {
                    Vector2i mousePos = Mouse::getPosition(window);
                   std:: cout <<"x : "<< mousePos.x << " " << "|| y : "<<mousePos.y << std::endl;
                    if (mousePos.x >= 254 && mousePos.x <= 439 && mousePos.y >= 282 && mousePos.y <= 345)
                    {
                    std::    cout << "Play";
                    startmusic.stop();
                    startmusic.play();
                    return 1; 
                    window.close();
                       
                    }

                    if (mousePos.x >= 254 && mousePos.x <= 439 && mousePos.y >= 376 && mousePos.y <= 437)
                    {
                        std::cout << "Exit";
                        quitmusic.stop();
                        quitmusic.play();
                        //window.close();
                    }

                    if (mousePos.x >= 270 && mousePos.x <= 340 && mousePos.y >= 470 && mousePos.y <= 535)
                    {
                      std::  cout << "sound ON";
                      music.play();
                      musicflag_bg = 1;
                    }
                    if (mousePos.x >= 360 && mousePos.x <= 430 && mousePos.y >= 468 && mousePos.y <= 535)
                    {
                        std::cout << "sound OFF ";
                        music.pause();
                        musicflag_bg =0;


                    }

                }
            
            }

            window.clear();
            window.draw(background);

           

            window.display();
        }
    return 0;
}

void gameover()
{
    Font font;
    font.loadFromFile("font2.ttf");
    Text text;											
    text.setFont(font);
    text.setCharacterSize(50);
    text.setString("Game Over");
    text.setPosition(10.f, 10.f);

    srand(time(0));

    Text nameText;
    nameText.setFont(font);
    nameText.setCharacterSize(50);
    nameText.setFillColor(Color::White);
    nameText.setPosition(10.f, 170.f);

    RenderWindow window2(VideoMode(1280, 720), "Checkmate");
    while (window2.isOpen())
    {
        Event e;
        while (window2.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window2.close();
            else if (e.key.code == Keyboard::Escape)
                window2.close();
            else if (e.key.code == Keyboard::Num1)
            {
                window2.close();
                display_menu();
            }
        }
        window2.clear();
        window2.draw(background);
        window2.draw(text);
        window2.display();
    } 
}
};