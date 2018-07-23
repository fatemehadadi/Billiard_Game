#include <SFML/Graphics.hpp>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <stdio.h>
#include "headers/renderer.h"
#include "headers/network.h"
#include "headers/resource.h"
#include <iostream>
using namespace sf;
void fonc(Network *network) {
    cout<<"started";
    network->listen();
}
bool quit=false;
char* get_ip(){
    struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;
    char *addr;

    getifaddrs (&ifap);
    for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr->sa_family==AF_INET) {
            sa = (struct sockaddr_in *) ifa->ifa_addr;
            addr = inet_ntoa(sa->sin_addr);
        }
    }
    freeifaddrs(ifap);
    return addr;
}
void find_list(){
    sf::UdpSocket socket;
    char *name=get_ip();
    char data[100];
    string m=" 12345";
    int t=0;
    for(int i=0;name[i]!='\0';i++){
        data[i]=name[i];
        t++;
    }
    for(int i=0;i<m.size();i++){
        data[i+t]=m[i];
    }
    while(!quit){
        socket.send(data,100,sf::IpAddress::Broadcast,12345);
        sf::sleep(milliseconds(50));
    }
}
int main() {
    //bool is_started= false;
    //bool is_chosen= false;
    RenderWindow window(sf::VideoMode(700, 500), "Billiard");  //main window
    Game game;
    game.is_started= false;
    game.is_chosen= false;
    bool not_listening=true;
    Resource* resource = new Resource(&game);
    Network* network;

    sf::Thread listening(&fonc,network);
    sf::Thread networklist(&find_list);
    networklist.launch();
    game.status="Welcome To Billiard Game!";
    while(window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                quit=true;
            }
            if(game.is_chosen== false){ //at the beginning
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        std::cout << "the right button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                        //play as server
                        if((event.mouseButton.x>250 && event.mouseButton.x<450)&&(event.mouseButton.y>145 && event.mouseButton.y<245)){
                            game.is_chosen=true;
                            network = new Network(resource);
                            network->is_server=true;
                            //network->listen();
                            game.is_listening= false;
                            game.status="choose your partner:";
                        }
                        //play as client
                        if((event.mouseButton.x>250 && event.mouseButton.x<450)&&(event.mouseButton.y>250 && event.mouseButton.y<350)){
                            game.is_chosen=true;
                            game.is_listening=true;
                            game.status="choose your partner:";
                            network = new Network(resource, "127.0.0.1");
                            network->is_server=false;
                            network->connect(&game);
                        }

                    }
                }

            }
            else if(game.is_started==false){ //just choose to be server or client
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        std::cout << "the right button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                        if((event.mouseButton.x>300 && event.mouseButton.x<400)&&(event.mouseButton.y>395 && event.mouseButton.y<445)){
                            if(game.status == "No player is available") {
                                game.is_chosen = false;
                                delete network;
                                game.status = "choose again";
                            }
                            else if(game.is_listening== false){
                                game.is_listening=true;
                            }
                            else{
                                game.is_started=true;
                                game.status="ready to play!";
                            }
                        }

                    }
                }
            }
            else{ //game is started
                if (event.type == sf::Event::MouseButtonPressed && game.is_your_turn)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        std::cout << "the right button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                        if(game.bulls_stoped()){
                            if(game.choose_color==false){

                            }
                            else if(game.choose_dir==false){

                            }
                            else if(game.choose_side==false){

                            }
                            else if(game.choose_speed==false){

                            }
                        }
                        if((event.mouseButton.x>300 && event.mouseButton.x<400)&&(event.mouseButton.y>395 && event.mouseButton.y<445)){

                        }

                    }
                }

            }
        }
        game.move();
        cout<<"out of move!\n";
        /*if((game.is_chosen && not_listening )&& network->is_server){
            listening.launch();
            not_listening=false;
        }*/
        if(game.is_started){
            network->send();
            network->receive();
        }
        window.clear();
        if(game.is_started){ //if the game is started
            render_game(&window,game);
        }
        else if(game.is_chosen){ //if is going to find player
            render_player(&window, &game);
        }
        else{ //if choose to be server or client
            render_type(&window);
        }
        window.display();
    }
    std::cout<<window.o;
    return 0;
}