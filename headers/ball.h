//
// Created by pure on 7/22/18.
//
#include <iostream>
#ifndef SNOOKER_BALL_H
#define SNOOKER_BALL_H
using namespace std;

class Ball{
public:
    Ball(string color,float score,float pos_x,float pos_y);
    string color;
    float score;
    float speed;
    float fa;
    float p[2];
    float v[2];
    float a[2];
    bool is_stoped();
};

#endif //SNOOKER_BALL_H
