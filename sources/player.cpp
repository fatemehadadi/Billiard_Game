//
// Created by pure on 7/22/18.
//

#include "../headers/player.h"
#include <algorithm>
Player::Player(int score, string address="0") {
    this->score=score;
    this->address=address;
    this->number=0;
}