//
// Created by pure on 7/12/18.
//
#include <iostream>
#ifndef BILL_BALL_H
#define BILL_BALL_H
using namespace std;

class Ball{
public:
    Ball(string color,float score,float pos_x,float pos_y);
    string color;
    float score;
    float p[2];
    float v[2];
    float a[2];
    bool is_stoped=true;
};
#endif //BILL_BALL_H
