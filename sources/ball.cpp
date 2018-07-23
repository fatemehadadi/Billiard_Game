//
// Created by pure on 7/22/18.
//
#include "../headers/ball.h"
#include <algorithm>
Ball::Ball(string color, float score, float pos_x, float pos_y) {
    this->color=color;
    this->score=score;
    this->p[0]=pos_x;
    this->p[1]=pos_y;
    this->v[0]=0;
    this->v[1]=0;
    this->a[0]=0;
    this->a[1]=0;
}
bool Ball::is_stoped() {
    if(p[0]==0 && p[1]==0)
        return true;
    return false;
}