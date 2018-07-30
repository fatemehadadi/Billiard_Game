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


bool quit=false; //for list of players thread
char* get_ip()
{ //get the ip to send for all players
    struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;
    char *addr;

    getifaddrs (&ifap);
    for (ifa = ifap; ifa; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr->sa_family==AF_INET)
        {
            sa = (struct sockaddr_in *) ifa->ifa_addr;
            addr = inet_ntoa(sa->sin_addr);
        }
    }
    freeifaddrs(ifap);
    return addr;
}

void find_list()
{ //thread for find all online players
    sf::UdpSocket socket;
    char *name=get_ip();
    sf::IpAddress a=sf::IpAddress::getPublicAddress();
    cout<<"******"<<a<<"*******\n";
    char data[100];
    string m=" 12345";
    int t=0;
    for(int i=0;name[i]!='\0';i++)
    {
        data[i]=name[i];
        t++;
    }
    for(int i=0;i<m.size();i++)
    {
        data[i+t]=m[i];
    }
    while(!quit)
    {
        socket.send(data,100,sf::IpAddress::Broadcast,12345);
        sf::sleep(milliseconds(50));
    }
}

int main()
{
    RenderWindow window(sf::VideoMode(700, 500), "Billiard");  //main window
    Game game;//main data of game shared between players
    game.is_started= false; //if game is ready to play
    game.is_chosen= false; //if the type of player is chosen
    game.status="Welcome To Billiard Game!"; //game status shows at top
    bool not_listening=true; //for find the availble player
    double speed,x,y; //for saving data of shoots
    Resource* resource = new Resource(&game);
    Network* network;

    sf::Thread networklist(&find_list); //thread for find all players
    networklist.launch(); //start the thread

    while(window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
                quit=true;
            }
            if(game.is_chosen== false)
            { //at the beginning
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
                            game.turn=1;
                            game.motion="Your Turn!\nSelect the speed:";
                            game.choose_color=false;
                            game.choose_dir=false;
                            game.choose_side=false;
                            game.choose_speed=false;
                            network->listen(&game);
                            game.is_listening= false;
                            game.status="choose your partner:";

                        }
                        //play as client
                        if((event.mouseButton.x>250 && event.mouseButton.x<450)&&(event.mouseButton.y>250 && event.mouseButton.y<350))
                        {
                            game.is_chosen=true;
                            game.is_listening=true;
                            game.turn=-1;
                            game.status="choose your partner:";
                            game.motion="Please wait!";
                            game.choose_color=false;
                            game.choose_dir=false;
                            game.choose_side=false;
                            game.choose_speed=false;
                            network = new Network(resource, "127.0.0.1");
                            network->is_server=false;
                            network->connect(&game);
                        }

                    }
                }

            }
            else if(game.is_started==false)
            { //just choose to be server or client
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        std::cout << "the right button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                        if(network->is_server)
                        {
                            network->listen(&game);
                        }
                        if((event.mouseButton.x>300 && event.mouseButton.x<400)&&(event.mouseButton.y>395 && event.mouseButton.y<445))
                        {
                            if(game.status == "No player is available")
                            {
                                game.is_chosen = false;
                                delete network;
                                game.status = "choose again";

                            }
                            else if(game.is_listening== false)
                            {
                                game.is_listening=true;
                            }
                            else{
                                if("0.0.0.0"!=network->socket->getRemoteAddress().toString())
                                {
                                    game.is_started=true;
                                    game.status="ready to play!";
                                }
                            }
                        }

                    }
                }
            }
            else
            { //game is started
                if (event.type == sf::Event::MouseButtonPressed && game.is_your_turn)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        std::cout << "the right button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                        if(game.bulls_stoped()){
                            if(game.choose_speed==false)
                            {
                                if((event.mouseButton.x>400 && event.mouseButton.x<600)&&(event.mouseButton.y>440 && event.mouseButton.y<460))
                                {
                                    speed=(event.mouseButton.x-400)/10;
                                    game.motion+=to_string((int)speed)+"\nchoose direction:";
                                    game.choose_speed=true;
                                }
                            }
                            else if(game.choose_dir==false)
                            {
                                if(sqrt(pow(event.mouseButton.x-520,2)+pow(event.mouseButton.y-330,2))<60)
                                {
                                    x=event.mouseButton.x;
                                    y=event.mouseButton.y;
                                    game.motion+="\nchosse side:";
                                    game.choose_dir=true;
                                }
                            }
                            else if(game.choose_side==false)
                            {
                                if(sqrt(pow(event.mouseButton.x-520,2)+pow(event.mouseButton.y-330,2))<60)
                                {
                                    if(x==520)
                                    {
                                        game.motion="";
                                        game.ball[0]->v[0]=0;
                                        game.ball[0]->v[1]=speed;
                                        if(y<330)game.ball[0]->v[1]*=-1;
                                        game.spin=(520-event.mouseButton.x)/(60);
                                        game.choose_side=true;
                                    }
                                    else
                                    {
                                        double teta=atan((y-330)/(x-520));
                                        game.motion="";
                                        game.ball[0]->v[0]=1*speed*cos(teta);
                                        game.ball[0]->v[1]=1*speed*sin(teta);
                                        game.spin=(520-event.mouseButton.x)/(60);
                                        game.choose_side=true;
                                    }
                                }
                            }
                            if(game.choose_color)
                            {

                            }
                        }
                    }
                }

            }
        }
        game.move();
        if((game.is_chosen && not_listening )&& network->is_server) //if is still wait for online player
        {
            not_listening=false;
        }
        if(game.is_started) //if there is data to send and recieve
        {
            if(game.turn==1) //if is server
            { //if is your turn
                game.check();
                network->send();
            }
            else
            { //if is next one turn
                game.check();
                network->receive();
            }
        }
        for(int i=0;i<22;i++) //lower the speed by friction
        {
            game.ball[i]->friction();
        }
        window.clear();
        if(game.is_started) 
        { //if the game is started
            render_game(&window,game);
        }
        else if(game.is_chosen)
        { //if is going to find player
            render_player(&window, &game,network);
        }
        else
        { //if choose to be server or client
            render_type(&window,&game);
        }
        window.display();
    }
    return 0;
}