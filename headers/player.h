//
// Created by pure on 7/12/18.
//

#ifndef BILL_PLAYER_H
#define BILL_PLAYER_H

#include <iostream>
using namespace std;

class Player{
public:
    Player(string, float, int, string);
    string name;
    float score;
    int turn;
    string address;
};
#endif //BILL_PLAYER_H
