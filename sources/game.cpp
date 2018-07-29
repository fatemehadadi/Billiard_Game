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
    ball[0]=new Ball("white",0,263-40,143) ;
    ball[1]=new Ball("yellow",2,170+73.7,177/2+55+29);
    ball[2]=new Ball("pink",6,170+(356/2+356-32.4)/2,177/2+55);
    ball[3]=new Ball("red",1,x+5.5,y);
    ball[4]=new Ball("red",1,x+5.5*2,y-r*2+r);
    ball[5]=new Ball("red",1,x+5.5*2,y+r);
    ball[6]=new Ball("red",1,x+5.5*3,y-r*3+r);
    ball[7]=new Ball("red",1,x+5.5*3,y);
    ball[8]=new Ball("red",1,x+5.5*3,y+r+r);
    ball[9]=new Ball("red",1,x+5.5*4,y-r*3);
    ball[10]=new Ball("red",1,x+5.5*4,y-r);
    ball[11]=new Ball("red",1,x+5.5*4,y+r);
    ball[12]=new Ball("red",1,x+5.5*4,y+r*3);
    ball[13]=new Ball("red",1,x+5.5*5,y-r*4);
    ball[14]=new Ball("red",1,x+5.5*5,y-r*2);
    ball[15]=new Ball("red",1,x+5.5*5,y);
    ball[16]=new Ball("red",1,x+5.5*5,y+r*2);
    ball[17]=new Ball("red",1,x+5.5*5,y+r*4);
    ball[18]=new Ball("green",3,170+73.7,177/2+55-29);
    ball[19]=new Ball("blue",5,170+356/2,177/2+55);
    ball[20]=new Ball("brown",4,170+73.7,177/2+55);
    ball[21]=new Ball("black",7,170+356-32.4,177/2+55);
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
bool Game::collision(float place[][3]){
    for(int i=0;i<22;i++){
        for(int j=i+1;j<22;j++){
            //if there is collision
            if((place[i][0]-place[j][0])*(place[i][0]-place[j][0])+(place[i][1]-place[j][1])*(place[i][1]-place[j][1])<(5.5)*(5.5)){
                return true;
            }
        }
    }
    return false;
}
float* Game::colli_place(Ball *b1,Ball *b2,float x,float y){
    float *f=new float [2];
    if(b1->v[0]*b1->v[0]<0.0001){
        f[0]=b1->p[0];
        f[1]=sqrt(pow(5.5,2)+pow(b1->p[0]-x,2));
        if(b1->v[1]>0)f[1]*=-1;
    }
    else{
        float m=b1->v[1]/b1->v[0];
        float h=b1->p[1]-m*b1->p[0];
        float a=m*m+1;
        float b=-2*x-2*m*(h-y);
        float c=x*x+pow(h-y,2)-pow(5.5,2);
        float delta=pow(b,2)-4*a*c;
        if(delta<-0.001){
            cout<<"errror!";
            f[0]=370;
            f[1]=80;
            return f;
        }
        else if(pow(delta,2)<0.01){
            f[0]=-b/(2*a);
        }
        else{
            if(b1->v[0]>0){
                f[0]=-1*max(-((-b+sqrt(delta))/2*a),-((-b-sqrt(delta))/2*a));
            }
            else{
                f[0]=max((-b+sqrt(delta))/2*a,(-b-sqrt(delta))/2*a);
            }
        }
        f[1]=m*f[0]+h;
    }
    return f;
}
bool Game::not_in_hole(float x,float y){
    //check all 6 holes
    return false;
}
bool Game::overborder(float place[][3]){
    float r=5.5/2;
    for(int i=0;i<22;i++){
        if(not_in_hole(place[i][0],place[i][1])){
            if(place[i][1]<55+r){
                return true;
            }
            else if(place[i][1]>55+177-r){
                return true;
            };
            if(place[i][0]<170+r){
                return true;
            }
            else if(place[i][0]>170+356-r){
                return true;
            };
        }
    }
    return false;
}

void Game::move() { //move the balls or play orders
    if(this->is_started){
        if(bulls_stoped() && this->turn==1){
            if(choose_speed){
            }
        }
        else if(bulls_stoped()==false){
            //ball are moving
            cout<<ball[0]->p[0]<<" "<<ball[0]->p[1]<<"\n";
            float place[22][3];
            for(int i=0;i<22;i++){
                for(int j=0;j<3;j++){
                    if(j==2)place[i][j]=0;
                    else{
                        place[i][j]=this->ball[i]->p[j]+this->ball[i]->v[j];
                    }
                }
            }
            double min,temp;
            while(collision(place) || overborder(place)){
                std::cout<<"collision! \n";
                double r=5.5/2;
                for(int i=0;i<22;i++){
                    if(not_in_hole(place[i][0],place[i][1])){
                        //check for white ball
                        //others
                        if(place[i][1]<55+r){
                            place[i][1]+=2*(55+r-place[i][1]);
                            ball[i]->v[1]*=-1;
                        }
                        else if(place[i][1]>55+177-r){
                            place[i][1]+=2*(55+177-r-place[i][1]);
                            ball[i]->v[1]*=-1;
                        };
                        if(place[i][0]<170+r){
                            place[i][0]+=2*(170+r-place[i][0]);
                            ball[i]->v[0]*=-1;
                        }
                        else if(place[i][0]>170+356-r){
                            place[i][0]+=2*(170+356-r-place[i][0]);
                            ball[i]->v[0]*=-1;
                        };
                    }
                    min=5.5*5.5;
                    for(int j=i+1;j<22;j++){
                        //if there is collision
                        temp=(place[i][0]-place[j][0])*(place[i][0]-place[j][0])+(place[i][1]-place[j][1])*(place[i][1]-place[j][1]);
                        if(temp<min){
                            min=temp;
                            place[i][2]=j;
                        }
                    }
                    //if there is collision
                    if(place[i][2]>0){
                        int t= static_cast<int>(place[i][2]);
                        double vi1=sqrt(pow(ball[i]->v[0],2)+pow(ball[i]->v[1],2));
                        double vi2=sqrt(pow(ball[t]->v[0],2)+pow(ball[t]->v[1],2));
                        if(vi1>vi2){
                            //find place of collision
                            float *f=colli_place(ball[i],ball[t],place[t][0],place[t][0]);
                            float x=f[0];
                            float y=f[1];
                            //insert new place in array of all places
                            place[i][0]=x;
                            place[i][1]=y;
                            place[i][2]=0;
                            //find teta
                            double teta;
                            if(pow(ball[i]->v[0],2)<0.01){
                                teta=atan(-1/((y-place[t][1])/(x-place[t][0])))-atan(1)*2;
                            }
                            else{
                                teta=atan(-1/((y-place[t][1])/(x-place[t][0])))-atan(ball[i]->v[1]/ball[i]->v[0]);
                            }
                            if(teta<0)teta*=-1;
                            if(teta>atan(1)*2)teta=atan(1)*4-teta;

                            //calculation for speeds
                            double alfa;
                            if(ball[t]->v[0]==0){
                                alfa=0;
                            }
                            else{
                                alfa=atan(-1/(ball[i]->v[1]/ball[i]->v[0]));
                            }
                            if(alfa<0)alfa*=-1;
                            if(alfa>atan((1)*4))alfa-=atan(1)*4;

                            double tekan=ball[t]->v[0]*cos(alfa)+ball[t]->v[1]*sin(alfa);
                            if(vi2<0.01){
                                tekan=0;
                            }
                            double k=pow(vi1,2)/2+pow(vi2,2)/2;
                            double vf1 = 0,vf2=0;

                            if(cos(teta)<0.0001){ //check possibility
                                if(pow(sin(2*teta),2)<0.0001){
                                    vf1=0;
                                }
                                else{
                                    vf1=tekan/sin(2*teta);
                                }
                            }
                            else{
                                double a=pow(sin(2*teta)/cos(teta),2)-1;
                                double b=(2*tekan*sin(2*teta))/-cos(teta);
                                double c=k-pow(tekan/cos(teta),2);
                                if(a*a<0.000001){
                                    if(c*c<0.000001){
                                        vf1=0;
                                    }
                                    else{
                                        vf1=-b/c;
                                    }
                                }
                                else{
                                    double delta=b*b-4*a*c;
                                    if(delta*delta<0.0001){
                                        vf1=-b/(2*a);
                                    }
                                    else if(delta>0){
                                        vf1=(-b-sqrt(delta))/(2*a);
                                    }
                                }
                            }
                            if(cos(teta)*cos(teta)<0.00001){
                                vf2=sqrt(k-vf1*vf1);
                            }
                            else{
                                vf2=(tekan-sin(2*teta))/-cos(teta);
                            }
                            //real speed in game
                            if(ball[i]->v[1]==0){
                                if(ball[i]->v[0]<0){//if we need to rotate like mirror
                                    ball[i]->v[0]=-vf1*cos(2*teta);
                                    ball[i]->v[1]=vf1*sin(2*teta);
                                    ball[t]->v[0]=-vf2*sin(teta);
                                    ball[t]->v[1]=vf2*cos(teta);
                                }
                                else{ //no rotation
                                    ball[i]->v[0]=vf1*cos(2*teta);
                                    ball[i]->v[1]=vf1*sin(2*teta);
                                    ball[t]->v[0]=vf2*sin(teta);
                                    ball[t]->v[1]=vf2*cos(teta);
                                }
                            }
                            else if(ball[i]->v[0]==0){ //if we need to rotate 90 degree
                                if(ball[i]->v[1]<0){
                                    ball[i]->v[1]=-vf1*cos(2*teta);
                                    ball[i]->v[0]=vf1*sin(2*teta);
                                    ball[t]->v[1]=-vf2*sin(teta);
                                    ball[t]->v[0]=vf2*cos(teta);
                                }
                                else{
                                    ball[i]->v[1]=vf1*cos(2*teta);
                                    ball[i]->v[0]=vf1*sin(2*teta);
                                    ball[t]->v[1]=vf2*sin(teta);
                                    ball[t]->v[0]=vf2*cos(teta);
                                }
                            }
                            else{ //if we need to rotate coordination
                                double beta=atan(ball[i]->v[1]/ball[i]->v[0]);
                                ball[i]->v[0]=vf1*cos(2*teta)*cos(beta)+vf1*sin(2*teta)*sin(beta);
                                ball[i]->v[1]=vf1*sin(2*teta)*cos(beta)+vf1*cos(2*teta)*sin(beta);
                                ball[t]->v[0]=vf2*sin(teta)*cos(beta)+vf2*cos(teta)*sin(beta);
                                ball[t]->v[1]=vf2*cos(teta)*cos(beta)+vf2*sin(teta)*sin(beta);
                            }
                        }
                        else{
                            //swap parameter
                            int j=i;
                            i=t;
                            t=j;
                            double tem=vi1;
                            vi1=vi2;
                            vi2=tem;

                            //find place of collision
                            float *f=colli_place(ball[i],ball[t],place[t][0],place[t][0]);
                            float x=f[0],y=f[1];
                            //insert new place in array of all places
                            place[i][0]=x;
                            place[i][1]=y;
                            place[i][2]=0;
                            place[t][2]=0;
                            //find teta
                            double teta;
                            if(pow(ball[i]->v[0],2)<0.01){
                                teta=atan(-1/((y-place[t][1])/(x-place[t][0])))-atan(1)*2;
                            }
                            else{
                                teta=atan(-1/((y-place[t][1])/(x-place[t][0])))-atan(ball[i]->v[1]/ball[i]->v[0]);
                            }
                            if(teta<0)teta*=-1;
                            if(teta>atan(1)*2)teta=atan(1)*4-teta;

                            //calculation for speeds
                            double alfa;
                            if(ball[t]->v[0]==0){
                                alfa=0;
                            }
                            else{
                                alfa=atan(-1/(ball[i]->v[1]/ball[i]->v[0]));
                            }
                            if(alfa<0)alfa*=-1;
                            if(alfa>atan((1)*4))alfa-=atan(1)*4;

                            double tekan=ball[t]->v[0]*cos(alfa)+ball[t]->v[1]*sin(alfa);
                            if(vi2<0.01){
                                tekan=0;
                            }
                            double k=pow(vi1,2)/2+pow(vi2,2)/2;
                            double vf1=0,vf2=0;

                            if(cos(teta)<0.0001){ //check possibility
                                if(pow(sin(2*teta),2)<0.0001){
                                    vf1=0;
                                }
                                else{
                                    vf1=tekan/sin(2*teta);
                                }
                            }
                            else{
                                double a=pow(sin(2*teta)/cos(teta),2)-1;
                                double b=(2*tekan*sin(2*teta))/-cos(teta);
                                double c=k-pow(tekan/cos(teta),2);
                                if(a*a<0.000001){
                                    if(c*c<0.000001){
                                        vf1=0;
                                    }
                                    else{
                                        vf1=-b/c;
                                    }
                                }
                                else{
                                    double delta=b*b-4*a*c;
                                    if(delta*delta<0.0001){
                                        vf1=-b/(2*a);
                                    }
                                    else if(delta>0){
                                        vf1=(-b-sqrt(delta))/(2*a);
                                    }
                                }
                            }
                            if(cos(teta)*cos(teta)<0.00001){
                                vf2=sqrt(k-vf1*vf1);
                            }
                            else{
                                vf2=(tekan-sin(2*teta))/-cos(teta);
                            }
                            //real speed in game
                            if(ball[i]->v[1]==0){
                                if(ball[i]->v[0]<0){//if we need to rotate like mirror
                                    ball[i]->v[0]=-vf1*cos(2*teta);
                                    ball[i]->v[1]=vf1*sin(2*teta);
                                    ball[t]->v[0]=-vf2*sin(teta);
                                    ball[t]->v[1]=vf2*cos(teta);
                                }
                                else{ //no rotation
                                    ball[i]->v[0]=vf1*cos(2*teta);
                                    ball[i]->v[1]=vf1*sin(2*teta);
                                    ball[t]->v[0]=vf2*sin(teta);
                                    ball[t]->v[1]=vf2*cos(teta);
                                }
                            }
                            else if(ball[i]->v[0]==0){ //if we need to rotate 90 degree
                                if(ball[i]->v[1]<0){
                                    ball[i]->v[1]=-vf1*cos(2*teta);
                                    ball[i]->v[0]=vf1*sin(2*teta);
                                    ball[t]->v[1]=-vf2*sin(teta);
                                    ball[t]->v[0]=vf2*cos(teta);
                                }
                                else{
                                    ball[i]->v[1]=vf1*cos(2*teta);
                                    ball[i]->v[0]=vf1*sin(2*teta);
                                    ball[t]->v[1]=vf2*sin(teta);
                                    ball[t]->v[0]=vf2*cos(teta);
                                }
                            }
                            else{ //if we need to rotate coordination
                                double beta=atan(ball[i]->v[1]/ball[i]->v[0]);
                                ball[i]->v[0]=vf1*cos(2*teta)*cos(beta)+vf1*sin(2*teta)*sin(beta);
                                ball[i]->v[1]=vf1*sin(2*teta)*cos(beta)+vf1*cos(2*teta)*sin(beta);
                                ball[t]->v[0]=vf2*sin(teta)*cos(beta)+vf2*cos(teta)*sin(beta);
                                ball[t]->v[1]=vf2*cos(teta)*cos(beta)+vf2*sin(teta)*sin(beta);
                            }
                            i=t;
                        }
                    }
                }

            }
            for(int i=0;i<22;i++){
                this->ball[i]->p[0]=place[i][0];
                this->ball[i]->p[1]=place[i][1];
            }
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
void Game::check() {

}