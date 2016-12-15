//
// Created by Quentin on 14/12/2016.
//

#include "../include/Player.h"

Player::Player() {

}

Player::Player(int id, const std::string &name, const glm::vec3 &position, const std::string &description) : Entity(
        id, name, position, description){

}

void Player::moveTo(glm::vec3 position) {

}
