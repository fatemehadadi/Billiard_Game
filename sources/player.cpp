//
// Created by pure on 7/12/18.
//
#include "../headers/player.h"
#include <algorithm>
Player::Player(string name, float score, int turn, string address="0") {
    this->name=name;
    this->score=score;
    this->turn=turn;
    this->address=address;
}