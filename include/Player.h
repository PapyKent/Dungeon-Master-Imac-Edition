//
// Created by Quentin on 14/12/2016.
//

#ifndef IMACGL_PLAYER_H
#define IMACGL_PLAYER_H


#include "Entity.h"

class Player : public Entity{
public :
    Player();
    Player(int id, const std::string &name, const glm::vec3 &position, const std::string &description);
    void moveTo(glm::vec3 position);


};


#endif //IMACGL_PLAYER_H
