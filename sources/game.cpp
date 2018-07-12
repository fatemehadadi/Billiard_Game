//
// Created by pure on 7/12/18.
//
#include "../headers/game.h"
#include <algorithm>
Game::Game() {
    me=new Player("me",0.0,0,"0");
    rival=new Player("rival",0.0,1,"0");

}
bool Game::is_your_turn() {
    return me->turn;
}