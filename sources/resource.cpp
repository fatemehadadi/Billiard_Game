//
// Created by pure on 7/22/18.
//

#include "../headers/resource.h"
#include <sstream>

Resource::Resource(Game *game) {
    this->game = game;
}

void Resource::set(std::string str) {
    /*std::stringstream inp(str);

    float p_position, ball_x, ball_y;
    inp >> p_position >> ball_x >> ball_y;
    this->game->set_position(1, p_position);
    this->game->get_ball()->set_x(ball_x);
    this->game->get_ball()->set_y(ball_y);
     */
    std::cout<<str<<"***"<<"is set"<<endl;
    return;
}

std::string Resource::get() {
    /*std::stringstream res;

    res << this->game->get_positions(0) << " "
        << this->game->get_ball()->get_x() << " "
        << this->game->get_ball()->get_y();

    return res.str();*/
    return "is get";
}
