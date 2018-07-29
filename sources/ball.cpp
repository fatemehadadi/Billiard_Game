//
// Created by pure on 7/22/18.
//
#include "../headers/ball.h"
#include <algorithm>
#include <utility>

Ball::Ball(string colour, float score, float pos_x, float pos_y) {
    this->color= std::move(colour);
    this->score=score;
    this->p[0]=pos_x;
    this->p[1]=pos_y;
    this->v[0]=0;
    this->v[1]=0;
    this->a[0]=0;
    this->a[1]=0;
}
bool Ball::is_stoped() {
    return p[0] == 0 && p[1] == 0;
}
void Ball::friction() {
    if(v[0]*v[0]<0.001){
        v[0]=0;
        if(v[1]*v[1]<0.001){
            v[1]=0;
        }
        else{
            if(v[1]>fic){
                v[1]-=fic;
            }
            else if(v[1]<0 && v[1]<-fic){
                v[1]+=fic;
            }
            else{
                v[1]=0;
            }
        }
    }
    else{
        double m=v[1]/v[0];
        if(v[0]<0){
            v[0]=v[0]+fic*cos(atan(m));
            if(v[0]>0)v[0]=0;

        }
        else if(v[0]>0){
            v[0]=v[0]-fic*cos(atan(m));
            if(v[0]<0){
                v[0]=0;
            }
        };
        if(v[1]<0){
            v[1]=v[1]+fic*sin(atan(m));
            if(v[1]>0)v[1]=0;

        }
        else if(v[1]>0){
            v[1]=v[1]-fic*sin(atan(m));
            if(v[1]<0)v[1]=0;
        };
    }
}