//
// Created by pure on 7/22/18.
//

#ifndef SNOOKER_RESOURCE_H
#define SNOOKER_RESOURCE_H

#include "game.h"
#include <string>

class Resource {
public:
    Resource(Game* game);

    void set(std::string);
    std::string get();
private:
    Game* game;
};

#endif //SNOOKER_RESOURCE_H
