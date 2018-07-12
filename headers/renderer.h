//
// Created by pure on 7/12/18.
//

#ifndef BILL_RENDERER_H
#define BILL_RENDERER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include "game.h"
#include "color.h"

std::string status;
using namespace sf;
using namespace std;

void background(sf::RenderWindow *window){
    sf::RectangleShape shape(sf::Vector2f(700, 500));
    shape.setPosition(0,0);
    shape.setFillColor(sf::Color::White);
    window->draw(shape);
}
void render_type(sf::RenderWindow *window){ //the beginning page //PAGE 1
    background(window);
    //status
    sf::Font font;
    if(! font.loadFromFile("arial.ttf")){
        cout<<"error!";
    }
    sf::Font font1;
    font1.loadFromFile("shooting-stars.ttf");
    sf::Text text;
    text.setFont(font1);
    text.setColor(sf::Color::Black);
    text.setCharacterSize(30);
    text.setPosition(180,100);
    text.setString(status);

    sf::Text text1;
    text1.setFont(font);
    text1.setColor(sf::Color::Black);
    text1.setCharacterSize(20);
    text1.setPosition(275,185);
    text1.setString("play as a server");

    sf::Text text2;
    text2.setFont(font);
    text2.setColor(sf::Color::Black);
    text2.setCharacterSize(20);
    text2.setPosition(275,290);
    text2.setString("play as a client");

    sf::RectangleShape shape(sf::Vector2f(200, 100));
    shape.setPosition(250,145);
    shape.setFillColor(sf::Color(88, 214, 141));
    shape.setOutlineThickness(5);
    shape.setOutlineColor(sf::Color( 247, 220, 111 ));

    sf::RectangleShape shape2(sf::Vector2f(200, 100));
    shape2.setPosition(250,260);
    shape2.setFillColor(sf::Color(88, 214, 141));
    shape2.setOutlineThickness(5);
    shape2.setOutlineColor(sf::Color( 247, 220, 111 ));

    window->draw(shape);
    window->draw(shape2);
    window->draw(text);
    window->draw(text1);
    window->draw(text2);
    /*sf::Vertex line[] =
            {
                    sf::Vertex(sf::Vector2f(10, 10)),
                    sf::Vertex(sf::Vector2f(150, 150))
            };
    line[1].color=sf::Color::Red;
    line[0].color=sf::Color::Red;
    window->draw(line, 2, sf::Lines);*/


}

void render_player(sf::RenderWindow *window){ //the player page //PAGE 2
    background(window);
    //status
    sf::Font font;
    if(! font.loadFromFile("arial.ttf")){
        cout<<"error!";
    }
    sf::Text text;
    text.setFont(font);
    text.setColor(sf::Color::Black);
    text.setCharacterSize(24);
    text.setPosition(220,20);
    text.setString(status);

    sf::Text text1;
    text1.setFont(font);
    text1.setColor(sf::Color::White);
    text1.setCharacterSize(20);
    text1.setPosition(320,410);
    text1.setString("PLAY");

    sf::RectangleShape shape(sf::Vector2f(100, 50));
    shape.setPosition(300,395);
    shape.setFillColor(sf::Color::Cyan);
    shape.setOutlineThickness(5);
    shape.setOutlineColor(sf::Color::Blue);

    window->draw(shape);
    window->draw(text);
    window->draw(text1);
}
void render_game(sf::RenderWindow *window,Game game){ //the game page //PAGE 3
    background(window);
    //status
    sf::RectangleShape shape0(sf::Vector2f(366, 187));
    shape0.setPosition(165,50);
    shape0.setFillColor(sf::Color::Blue);

    /*sf::Texture texture;
    if (!texture.loadFromFile("image.jpg"))
    {
        // error...
    }
    shape0.setTexture(&texture); // texture is a sf::Texture
    shape0.setTextureRect(sf::IntRect(10, 10, 100, 100));*/

    sf::RectangleShape shape(sf::Vector2f(356, 177));
    shape.setPosition(170,55);
    shape.setFillColor(sf::Color::Green);

    sf::RectangleShape shape1(sf::Vector2f(100, 50));
    shape1.setPosition(50,395);
    shape1.setFillColor(sf::Color::Yellow);

    sf::RectangleShape shape2(sf::Vector2f(100, 50));
    shape2.setPosition(170,395);
    shape2.setFillColor(sf::Color::Yellow);



    window->draw(shape0);
    window->draw(shape);
    window->draw(shape1);
    window->draw(shape2);



}
#endif //BILL_RENDERER_H
