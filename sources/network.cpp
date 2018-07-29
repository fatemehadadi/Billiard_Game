//
// Created by pure on 7/22/18.
//

#ifndef SNOOKER_NETWORK_H
#define SNOOKER_NETWORK_H
#include "resource.h"
#include <SFML/Network.hpp>


class Network {
public:
    Network(Resource* resource);
    Network(Resource* resource, std::string ip);

    void send();
    void receive();
    void listen(Game *);
    void connect(Game *);
    bool is_server;
    sf::TcpSocket* socket;


private:
    Resource* resource;
    std::string ip;
    sf::TcpListener* listener;
};


#endif //SNOOKER_NETWORK_H
