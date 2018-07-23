//
// Created by pure on 7/22/18.
//

#ifndef SNOOKER_GAME_H
#define SNOOKER_GAME_H
#include "ball.h"
#include "player.h"
#include <iostream>
using namespace std;

class Game{
public:
    Game();
    Player *me,*rival;
    Ball **ball;
    string status, list;
    int selectedV=0;
    bool is_your_turn=true, choose_color, choose_dir, choose_side, choose_speed, is_started, is_chosen, is_listening;
    bool bulls_stoped();
    int turn;
    bool is_new(string);
    void move();

};

#endif //SNOOKER_GAME_H
