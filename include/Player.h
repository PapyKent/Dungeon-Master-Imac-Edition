//
// Created by Quentin on 14/12/2016.
//

#ifndef IMACGL_PLAYER_H
#define IMACGL_PLAYER_H


#include "Entity.h"
#include "Camera.h"

class Player : public Entity{
public :
    Camera* camera;

    Player();
    Player(int id, const std::string &name, const glm::vec3 &position, const std::string &description);
    void moveLeft(float t);
    void moveFront(float t);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    void moveTo(glm::vec3 position);
    glm::vec3 getPosition();


};


#endif //IMACGL_PLAYER_H
