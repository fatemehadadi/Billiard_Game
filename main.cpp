#include <SFML/Graphics.hpp>
#include "headers/renderer.h"
#include <iostream>

using namespace sf;


int main() {
    bool is_started= false;
    bool is_chosen=false;
    RenderWindow window(sf::VideoMode(700, 500), "Billiard");  //main window
    Game game;
    status="Welcome To Billiard Game!";
    while(window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if(is_chosen== false){ //at the beginning
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        std::cout << "the right button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                        if((event.mouseButton.x>250 && event.mouseButton.x<450)&&(event.mouseButton.y>145 && event.mouseButton.y<245)){
                            is_chosen=true;
                            status="choose your partner:";
                        }
                        if((event.mouseButton.x>250 && event.mouseButton.x<450)&&(event.mouseButton.y>250 && event.mouseButton.y<350)){
                            is_chosen=true;
                            status="choose your partner:";
                        }

                    }
                }

            }
            else if(is_started==false){ //just choose to be server or client
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        std::cout << "the right button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                        if((event.mouseButton.x>300 && event.mouseButton.x<400)&&(event.mouseButton.y>395 && event.mouseButton.y<445)){
                            is_started=true;
                            status="ready to play!";
                        }

                    }
                }
            }
            else{ //game is started
                if (event.type == sf::Event::MouseButtonPressed && game.is_your_turn())
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        std::cout << "the right button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                        if((event.mouseButton.x>300 && event.mouseButton.x<400)&&(event.mouseButton.y>395 && event.mouseButton.y<445)){

                        }

                    }
                }

            }
        }
        window.clear();
        if(is_started){ //if the game is started
            render_game(&window,game);
        }
        else if(is_chosen){ //if is going to find player
            render_player(&window);
        }
        else{ //if choose to be server or client
            render_type(&window);
        }
        window.display();
    }
    return 0;
}