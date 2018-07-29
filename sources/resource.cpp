//
// Created by pure on 7/22/18.
//

#include "../headers/resource.h"

sf::Packet& operator <<(sf::Packet& packet, Ball *&ball)
{
    return packet << ball->color<<ball->score<<ball->p[0]<<ball->p[1]<<ball->v[0]<<ball->v[1]<<ball->a[0]<<ball->a[1];
}

sf::Packet& operator >>(sf::Packet& packet, Ball *&ball)
{
    return packet >> ball->color>>ball->score>>ball->p[0]>>ball->p[1]>>ball->v[0]>>ball->v[1]>>ball->a[0]>>ball->a[1];
}

Resource::Resource(Game *game) {
    this->game = game;
}

void Resource::set(sf::Packet &pack) { //for network.set
    /*std::stringstream inp(str);

    float p_position, ball_x, ball_y;
    inp >> p_position >> ball_x >> ball_y;
    this->game->set_position(1, p_position);
    this->game->get_ball()->set_x(ball_x);
    this->game->get_ball()->set_y(ball_y);
     */
    string str;
    pack>>str;
    for(int i=0;i<22;i++){
        pack>>game->ball[i];
    }
}
sf::Packet Resource::get() {  //for network.send
    /*std::stringstream res;

    res << this->game->get_positions(0) << " "
        << this->game->get_ball()->get_x() << " "
        << this->game->get_ball()->get_y();

    return res.str();*/

    sf::Packet pack;
    pack<<"ok";
    for(int i=0;i<22;i++){
        pack<<game->ball[i];
    }
    pack>>game->spin;
    return pack;
}
