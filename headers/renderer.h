//
// Created by pure on 7/22/18.
//

#ifndef SNOOKER_RENDERER_H
#define SNOOKER_RENDERER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include "game.h"
#include "network.h"
#include <sstream>

std::string status;
using namespace sf;
using namespace std;

void background(sf::RenderWindow *window){
    sf::RectangleShape shape(sf::Vector2f(700, 500));
    shape.setPosition(0,0);
    shape.setFillColor(sf::Color::White);
    window->draw(shape);
}
void render_type(sf::RenderWindow *window,Game *game){ //the beginning page //PAGE 1
    background(window);
    //status
    sf::Font font;
    if(! font.loadFromFile("arial.ttf")){
        cout<<"error!";
    }
    sf::Font font2;
    if(! font2.loadFromFile("dam.ttf")){
        cout<<"error!";
    }
    sf::Font font1;
    font1.loadFromFile("shooting-stars.ttf");
    sf::Text text;
    text.setFont(font1);
    text.setColor(sf::Color::Black);
    text.setCharacterSize(30);
    text.setPosition(180,50);
    text.setString(game->status);

    sf::Text text1;
    text1.setFont(font2);
    text1.setColor(sf::Color::Black);
    text1.setCharacterSize(24);
    text1.setPosition(270,180);
    text1.setString("play as a server");

    sf::Text text2;
    text2.setFont(font2);
    text2.setColor(sf::Color::Black);
    text2.setCharacterSize(24);
    text2.setPosition(270,290);
    text2.setString("play as a client");

    sf::RectangleShape shape(sf::Vector2f(200, 100));
    shape.setPosition(250,145);
    shape.setFillColor(sf::Color(  198, 82, 248  ));
    shape.setOutlineThickness(5);
    shape.setOutlineColor(sf::Color(   16, 225, 171
    ));

    sf::RectangleShape shape2(sf::Vector2f(200, 100));
    shape2.setPosition(250,260);
    shape2.setFillColor(sf::Color( 198, 82, 248  ));
    shape2.setOutlineThickness(5);
    shape2.setOutlineColor(sf::Color(   16, 225, 171 ));

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

void render_player(sf::RenderWindow *window, Game *game,Network *network){ //the player page //PAGE 2
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
    text.setString(game->status);

    sf::Text ls;
    ls.setFont(font);
    ls.setColor(sf::Color::Black);
    ls.setCharacterSize(16);
    ls.setPosition(220,70);
    stringstream str;
    string list_text=network->socket->getRemoteAddress().toString();
    if(list_text=="0.0.0.0")list_text="empty!";
    ls.setString("people in network:\n\n"+game->list+"\nloading...\n\nAvailable player:\n"+list_text);

    sf::Text text1;
    text1.setFont(font);
    text1.setColor(sf::Color::White);
    text1.setCharacterSize(20);
    text1.setPosition(320,410);
    if(game->status=="No player is available"){
        text1.setString("Back");
    }
    else if(game->is_listening==false){
        text1.setString("Start");
    }
    else{
        text1.setString("PLAY");
    }

    sf::RectangleShape shape(sf::Vector2f(100, 50));
    shape.setPosition(300,395);
    shape.setFillColor(sf::Color::Cyan);
    shape.setOutlineThickness(5);
    shape.setOutlineColor(sf::Color::Blue);

    window->draw(shape);
    window->draw(text);
    window->draw(text1);
    window->draw(ls);
}
void render_game(sf::RenderWindow *window,Game game){ //the game page //PAGE 3
    background(window);
    sf::Font font;
    if(! font.loadFromFile("arial.ttf")){
        cout<<"error!";
    }
    sf::Font font1;
    font1.loadFromFile("shooting-stars.ttf");
    sf::Text text;
    text.setFont(font1);
    text.setColor(sf::Color::Black);
    text.setCharacterSize(24);
    text.setPosition(180,10);
    text.setString(game.status);

    sf::Text command;
    command.setFont(font);
    command.setColor(sf::Color(  150, 46, 194  ));
    command.setCharacterSize(12);
    command.setPosition(20,30);
    string msg=game.motion;
    command.setString(msg);

    sf::RectangleShape shape0(sf::Vector2f(366, 187));
    shape0.setPosition(165,50);
    shape0.setFillColor(sf::Color( 205, 181, 75 ));

    sf::CircleShape uplefthole(4) ,downlefthole(4),centerupole(4),centerdownhole(4),uprighthole(4),downrighthole(4);
    uplefthole.setFillColor(sf::Color::Black);
    uprighthole.setFillColor(sf::Color::Black);
    centerupole.setFillColor(sf::Color::Black);
    downlefthole.setFillColor(sf::Color::Black);
    centerdownhole.setFillColor(sf::Color::Black);
    downrighthole.setFillColor(sf::Color::Black);
    uplefthole.setPosition(170-4,55-4);
    downlefthole.setPosition(170-4,55-4+177);
    centerdownhole.setPosition(170-4+356/2,55-4+177);
    centerupole.setPosition(170-4+356/2,55-4);
    uprighthole.setPosition(170-4+356,55-4);
    downrighthole.setPosition(170-4+356,55-4+177);



    /*sf::Texture texture;
    if (!texture.loadFromFile("image.jpg"))
    {
        // error...
    }
    shape0.setTexture(&texture); // texture is a sf::Texture
    shape0.setTextureRect(sf::IntRect(10, 10, 100, 100));*/

    sf::RectangleShape shape(sf::Vector2f(356, 177));
    shape.setPosition(170,55);
    shape.setFillColor(sf::Color( 46, 184, 48 ));

    sf::Vertex line[] =
            {
                    sf::Vertex(sf::Vector2f(170+73.7, 55)),
                    sf::Vertex(sf::Vector2f(170+73.7, 177+55))
            };
    line[1].color=sf::Color::Black;
    line[0].color=sf::Color::Black;
    /*window->draw(line, 2, sf::Lines);*/

    sf::CircleShape circle(29);
    circle.setPosition(170+73.7-29,177/2+55-29);
    circle.setFillColor(sf::Color( 46, 184, 48 ));
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(1);

    sf::RectangleShape center(sf::Vector2f(30,60));
    center.setPosition(170+73.7, 50+63);
    center.setFillColor(sf::Color( 46, 184, 48 ));

    sf::CircleShape dot(2);
    dot.setFillColor(sf::Color::Black);
    dot.setPosition(170+73.7-2,177/2+55-2);

    sf::CircleShape white_ball(2.75),yellow_ball(2.75),pink_ball(2.75),
            red1_ball(2.75),red2_ball(2.75),red3_ball(2.75),red4_ball(2.75),red5_ball(2.75),
            red6_ball(2.75),red7_ball(2.75),red8_ball(2.75),red9_ball(2.75),red10_ball(2.75),
            red11_ball(2.75),red12_ball(2.75),red13_ball(2.75),red14_ball(2.75),red15_ball(2.75),
            green_ball(2.75), blue_ball(2.75),brown_ball(2.75), black_ball(2.75)
    ;
    white_ball.setFillColor(sf::Color::White);
    yellow_ball.setFillColor(sf::Color::Yellow);
    pink_ball.setFillColor(sf::Color(242, 136, 204));
    red1_ball.setFillColor(sf::Color::Red);
    red2_ball.setFillColor(sf::Color::Red);
    red3_ball.setFillColor(sf::Color::Red);
    red4_ball.setFillColor(sf::Color::Red);
    red5_ball.setFillColor(sf::Color::Red);
    red6_ball.setFillColor(sf::Color::Red);
    red7_ball.setFillColor(sf::Color::Red);
    red8_ball.setFillColor(sf::Color::Red);
    red9_ball.setFillColor(sf::Color::Red);
    red10_ball.setFillColor(sf::Color::Red);
    red11_ball.setFillColor(sf::Color::Red);
    red12_ball.setFillColor(sf::Color::Red);
    red13_ball.setFillColor(sf::Color::Red);
    red14_ball.setFillColor(sf::Color::Red);
    red15_ball.setFillColor(sf::Color::Red);
    green_ball.setFillColor(sf::Color::Green);
    blue_ball.setFillColor(sf::Color::Blue);
    brown_ball.setFillColor(sf::Color(130, 70, 26));
    black_ball.setFillColor(sf::Color::Black);

    float r=2.75;
    int i=2;
    white_ball.setPosition(game.ball[0]->p[0]-r,game.ball[0]->p[1]-r);
    yellow_ball.setPosition(game.ball[1]->p[0]-r,game.ball[1]->p[1]-r);
    pink_ball.setPosition(game.ball[i]->p[0]-r,game.ball[i]->p[1]-r);i++;
    red1_ball.setPosition(game.ball[i]->p[0]-r,game.ball[i]->p[1]-r);i++;
    red2_ball.setPosition(game.ball[i]->p[0]-r,game.ball[i]->p[1]-r);i++;
    red3_ball.setPosition(game.ball[i]->p[0]-r,game.ball[i]->p[1]-r);i++;
    red4_ball.setPosition(game.ball[i]->p[0]-r,game.ball[i]->p[1]-r);i++;
    red5_ball.setPosition(game.ball[i]->p[0]-r,game.ball[i]->p[1]-r);i++;
    red6_ball.setPosition(game.ball[i]->p[0]-r,game.ball[i]->p[1]-r);i++;
    red7_ball.setPosition(game.ball[i]->p[0]-r,game.ball[i]->p[1]-r);i++;
    red8_ball.setPosition(game.ball[i]->p[0]-r,game.ball[i]->p[1]-r);i++;
    red9_ball.setPosition(game.ball[i]->p[0]-r,game.ball[i]->p[1]-r);i++;
    red10_ball.setPosition(game.ball[i]->p[0]-r,game.ball[i]->p[1]-r);i++;
    red11_ball.setPosition(game.ball[i]->p[0]-r,game.ball[i]->p[1]-r);i++;
    red12_ball.setPosition(game.ball[i]->p[0]-r,game.ball[i]->p[1]-r);i++;
    red13_ball.setPosition(game.ball[i]->p[0]-r,game.ball[i]->p[1]-r);i++;
    red14_ball.setPosition(game.ball[i]->p[0]-r,game.ball[i]->p[1]-r);i++;
    red15_ball.setPosition(game.ball[i]->p[0]-r,game.ball[i]->p[1]-r);i++;
    green_ball.setPosition(game.ball[i]->p[0]-r,game.ball[i]->p[1]-r);i++;
    blue_ball.setPosition(game.ball[i]->p[0]-r,game.ball[i]->p[1]-r);i++;
    brown_ball.setPosition(game.ball[i]->p[0]-r,game.ball[i]->p[1]-r);i++;
    black_ball.setPosition(game.ball[i]->p[0]-r,game.ball[i]->p[1]-r);i++;

    sf::CircleShape yellow,pink,red,blue,green,brown,black;
    yellow.setRadius(20);
    pink.setRadius(20);
    red.setRadius(20);
    green.setRadius(20);
    blue.setRadius(20);
    brown.setRadius(20);
    black.setRadius(20);
    yellow.setPosition(50,300);
    pink.setPosition(50+50,300);
    red.setPosition(50+100,300);
    green.setPosition(50+150,300);
    blue.setPosition(50+200,300);
    brown.setPosition(50+250,300);
    black.setPosition(50+300,300);
    yellow.setFillColor(sf::Color::Yellow);
    pink.setFillColor(sf::Color( 242, 136, 204));
    red.setFillColor(sf::Color::Red);
    green.setFillColor(sf::Color::Green);
    blue.setFillColor(sf::Color::Blue);
    brown.setFillColor(sf::Color(130, 70, 26));
    black.setFillColor(sf::Color::Black);

    sf::CircleShape shoot(60); //520, 330
    shoot.setFillColor(sf::Color::White);
    shoot.setOutlineThickness(2);
    shoot.setOutlineColor(sf::Color::Black);
    shoot.setPosition(460,270);
    sf::CircleShape shootdot(2);
    shootdot.setFillColor(sf::Color::Black);
    shootdot.setPosition(460+60-2,270+60-2);

    sf::Text your_speed,set;
    your_speed.setFont(font);
    your_speed.setColor(sf::Color::Black);
    your_speed.setCharacterSize(16);
    your_speed.setPosition(400,410);
    your_speed.setString("speed: "+to_string(game.selectedV));
    set.setFont(font);
    set.setColor(sf::Color(40, 96, 94));
    set.setCharacterSize(18);
    set.setPosition(632,435);
    set.setString("set");
    sf::RectangleShape set_cover(sf::Vector2f(36,20));
    set_cover.setFillColor(sf::Color::White);
    set_cover.setOutlineColor(sf::Color( 21, 187, 182 ));
    set_cover.setOutlineThickness(3);
    set_cover.setPosition(627,438);
    sf::Vertex speed[] =
            {
                    sf::Vertex(sf::Vector2f(400, 450)),
                    sf::Vertex(sf::Vector2f(600, 450))
            };
    speed[1].color=sf::Color::Black;
    speed[0].color=sf::Color::Black;
    /*window->draw(line, 2, sf::Lines);*/
    sf::CircleShape vstart(2);
    vstart.setFillColor(sf::Color::Black);
    vstart.setPosition(400-2,450-2);
    sf::CircleShape vmin(2);
    vmin.setFillColor(sf::Color::Black);
    vmin.setPosition(500-2,450-2);
    sf::CircleShape vmax(2);
    vmax.setFillColor(sf::Color::Black);
    vmax.setPosition(600-2,450-2);

    sf::Text your_score,scores;
    your_score.setFont(font);
    your_score.setColor(sf::Color::Black);
    your_score.setCharacterSize(20);
    your_score.setPosition(60,370);
    your_score.setString("score:");
    scores.setFont(font);
    scores.setColor(sf::Color::Black);
    scores.setCharacterSize(16);
    scores.setPosition(60,405);
    scores.setString(to_string(game.me->score));
    sf::RectangleShape shape1(sf::Vector2f(100, 50));
    shape1.setPosition(50,395);
    shape1.setFillColor(sf::Color::Yellow);

    sf::Text rival_score,rscores;
    rival_score.setFont(font);
    rival_score.setColor(sf::Color::Black);
    rival_score.setCharacterSize(20);
    rival_score.setPosition(60+120,370);
    rival_score.setString("rival:");
    rscores.setFont(font);
    rscores.setCharacterSize(16);
    rscores.setColor(sf::Color::Black);
    rscores.setPosition(180,405);
    rscores.setString(to_string(game.rival->score));
    sf::RectangleShape shape2(sf::Vector2f(100, 50));
    shape2.setPosition(170,395);
    shape2.setFillColor(sf::Color::Yellow);



    window->draw(text);
    window->draw(command);
    window->draw(shape0);
    window->draw(uplefthole);
    window->draw(downlefthole);
    window->draw(centerdownhole);
    window->draw(centerupole);
    window->draw(uprighthole);
    window->draw(downrighthole);

    window->draw(shape);
    window->draw(circle);
    window->draw(center);
    window->draw(line, 2, sf::Lines);
    window->draw(dot);
    window->draw(white_ball);
    window->draw(yellow_ball);
    window->draw(pink_ball);
    window->draw(red1_ball);
    window->draw(red2_ball);
    window->draw(red3_ball);
    window->draw(red4_ball);
    window->draw(red5_ball);
    window->draw(red6_ball);
    window->draw(red7_ball);
    window->draw(red8_ball);
    window->draw(red9_ball);
    window->draw(red10_ball);
    window->draw(red11_ball);
    window->draw(red12_ball);
    window->draw(red13_ball);
    window->draw(red14_ball);
    window->draw(red15_ball);
    window->draw(green_ball);
    window->draw(blue_ball);
    window->draw(brown_ball);
    window->draw(black_ball);



    window->draw(yellow);
    window->draw(pink);
    window->draw(red);
    window->draw(green);
    window->draw(blue);
    window->draw(brown);
    window->draw(black);

    window->draw(shape1);
    window->draw(your_score);
    window->draw(scores);
    window->draw(shape2);
    window->draw(rival_score);
    window->draw(rscores);
    window->draw(shoot);
    window->draw(shootdot);
    window->draw(speed, 2, sf::Lines);
    window->draw(your_speed);
    window->draw(set_cover);
    window->draw(set);
    window->draw(vstart);
    window->draw(vmin);
    window->draw(vmax);


}

#endif //SNOOKER_RENDERER_H
