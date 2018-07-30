//
// Created by pure on 7/22/18.
//

#include "../headers/resource.h"


//over write operators for Balls objects in packet
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

void Resource::set(sf::Packet &pack) { //for network.set //is client
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
    int temp;
    pack>>temp;
    if(temp!=game->turn){
        game->motion="Your Turn!\nSelect the speed:";
        game->choose_color=false;
        game->choose_dir=false;
        game->choose_side=false;
        game->choose_speed=false;
        game->turn=temp;
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
    pack<<-1*game->turn;
    return pack;
}
