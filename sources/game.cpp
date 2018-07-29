//
// Created by pure on 7/22/18.
//

#include "../headers/game.h"
#include <SFML/Network.hpp>
#include <algorithm>
Game::Game() {
    me=new Player(0,"0");
    rival=new Player(0,"0");
    spin=0;
    float r=2.75;
    float x=170+(356/2+356-32.4)/2,
            y=177/2+55;
    ball=new Ball *[22];
    ball[0]=new Ball("white",0,263-40-r,143-r) ;
    ball[1]=new Ball("yellow",2,170+73.7-r,177/2+55+29-r);
    ball[2]=new Ball("pink",6,170+(356/2+356-32.4)/2-r,177/2+55-r);
    ball[3]=new Ball("red",1,x+5.5-r,y-r);
    ball[4]=new Ball("red",1,x+5.5*2-r,y-r*2);
    ball[5]=new Ball("red",1,x+5.5*2-r,y);
    ball[6]=new Ball("red",1,x+5.5*3-r,y-r*3);
    ball[7]=new Ball("red",1,x+5.5*3-r,y-r);
    ball[8]=new Ball("red",1,x+5.5*3-r,y+r);
    ball[9]=new Ball("red",1,x+5.5*4-r,y-r*4);
    ball[10]=new Ball("red",1,x+5.5*4-r,y-r*2);
    ball[11]=new Ball("red",1,x+5.5*4-r,y);
    ball[12]=new Ball("red",1,x+5.5*4-r,y+r*2);
    ball[13]=new Ball("red",1,x+5.5*5-r,y-r*5);
    ball[14]=new Ball("red",1,x+5.5*5-r,y-r*3);
    ball[15]=new Ball("red",1,x+5.5*5-r,y-r);
    ball[16]=new Ball("red",1,x+5.5*5-r,y+r);
    ball[17]=new Ball("red",1,x+5.5*5-r,y+r*3);
    ball[18]=new Ball("green",3,170+73.7-r,177/2+55-r-29);
    ball[19]=new Ball("blue",5,170+356/2-r,177/2+55-r);
    ball[20]=new Ball("brown",4,170+73.7-r,177/2+55-r);
    ball[21]=new Ball("black",7,170+356-32.4-r,177/2+55-r);
    turn =1;
    choose_color= false;
    choose_dir= false;
    choose_side=false;
    choose_speed=false;

}
bool Game::bulls_stoped() {
    for(int i=0;i<22;i++){
        if (ball[i]->v[0]!=0 || ball[i]->v[1]!=0){
            return false;
        }
    }
    return true;
}
void Game::move() { //move the balls or play orders
    if(this->is_started){
        if(bulls_stoped() && this->turn==1){
            if(choose_speed){

            }
        }
        else{

        }
    }
    else if(this->is_chosen ){
        sf::UdpSocket socket;

        // bind the socket to a port
        sf::SocketSelector bs;
        bs.add(socket);
        /*if(bs.wait(sf::milliseconds(5))){
            if(bs.isReady(socket)){
                if (socket.bind(12345) != sf::Socket::Done)
                {
                    // error...
                    cout<<"cant bind the port!\n";
                }
            }
        }*/
        if (socket.bind(12345) != sf::Socket::Done)
        {
            // error...
            cout<<"cant bind the port!\n";
        }
        sf::IpAddress sender;
        unsigned short port;
        char data[100];
        std::size_t received;
        sf::SocketSelector selector;
        selector.add(socket);
        if(selector.wait(sf::seconds(5))){
            if(selector.isReady(socket)){
                if (socket.receive(data, 100, received, sender, port) != sf::Socket::Done)
                {
                    // error...
                    cout<<"cant receive!\n";
                }
                string msg;
                for(int i=0;data[i]!='\0';i++){
                    msg+=data[i];
                }
                if(is_new(msg)){
                    this->list+=msg+"\n";
                }
            }
        }


    }
}
bool Game::is_new(string m) {
    string temp;
    temp="";
    int k=1;
    for(int i=0;i<this->list.length();i+=k){
        for(int j=i;j<this->list.length();j++){
            temp+=this->list[j];
            if(this->list[j]=='\n'){
                if(temp==m+"\n")return false;
                k=j-i+1;
                temp="";
            }
        }
    }
    return true;
}