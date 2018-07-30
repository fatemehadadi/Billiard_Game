//
// Created by pure on 7/22/18.
//

#include "../headers/network.h"
#include <SFML/Network.hpp>

Network::Network(Resource *resource) {
    this->resource = resource;
    this->is_server = true;
    this->ip = "0.0.0.0";

    this->listener = new sf::TcpListener;

    listener->listen(12345);
}

Network::Network(Resource *resource, std::string ip) {
    this->resource = resource;
    this->is_server = false;
    this->ip = ip;
}

void Network::listen(Game *game) {
    if (this->is_server) {
        sf::SocketSelector selector;
        selector.add(*this->listener);
        if (selector.wait(sf::seconds(5)))
        {
                if (selector.isReady(*this->listener))
                {
                    this->socket = new sf::TcpSocket;
                    game->con_status=this->listener->accept(*this->socket);
                }
        }

    }
}

void Network::connect(Game *game) {
    if (not this->is_server){
        this->socket = new sf::TcpSocket;
        game->con_status =this->socket->connect(this->ip, 12345);
        if (game->con_status != sf::Socket::Done)
        {
            // error...
            game->status="No player is available";
        }
    }
}

void Network::send() {
    sf::Packet pack=this->resource->get();
    this->socket->send(pack);
    /*
    std::string message = this->resource->get();
    char* c_message = new char[(int)message.size() + 1];

    for (int i = 0; i < message.size(); i++)
        c_message[i] = message[i];

    this->socket->send(c_message, (int)message.size());

    delete c_message;*/
}

void Network::receive() {
    /*char data[100];
    size_t received;
    sf::sleep(sf::milliseconds(50));
    this->socket->receive(data, 100, received);

    if (received != 0) {
        std::string message = std::string(data);

        this->resource->set(message);
    }*/
    sf::Packet pack;
    this->socket->receive(pack);
    this->resource->set(pack);
}
