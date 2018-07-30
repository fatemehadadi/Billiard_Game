//
// Created by pure on 7/22/18.
//

#ifndef SNOOKER_GAME_H
#define SNOOKER_GAME_H
#include "ball.h"
#include "player.h"
#include <iostream>
#include <SFML/Network/Socket.hpp>

using namespace std;

class Game{
public:
    Game();
    Player *me,*rival;
    Ball **ball;
    string status, list, motion;
    int selectedV=0;
    sf::Socket::Status con_status;
    bool is_your_turn=true, choose_color, choose_dir, choose_side, choose_speed, is_started, is_chosen, is_listening;
    bool bulls_stoped();
    int turn;
    bool is_new(string);
    void check();
    bool collision(float [][3]);
    float* colli_place(Ball*,Ball*,float,float);
    bool not_in_hole(float,float);
    bool overborder(float [][3]);
    void move();
    float spin;

};

#endif //SNOOKER_GAME_H
