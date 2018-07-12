//
// Created by pure on 7/12/18.
//

#ifndef BILL_GAME_H
#define BILL_GAME_H

#include "ball.h"
#include "player.h"
#include "color.h"
#include <iostream>
using namespace std;

class Game{
public:
    Game();
    Player *me,*rival;
    Ball *b;
    bool is_your_turn();


};

#endif //BILL_GAME_H
