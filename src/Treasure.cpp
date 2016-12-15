//
// Created by Quentin on 14/12/2016.
//

#include "../include/Treasure.h"

Treasure::Treasure() {

}

Treasure::Treasure(int id, const std::string &name, const glm::vec3 &position, const std::string &description) : Entity(
        id, name, position, description){

}

void Treasure::moveTo(glm::vec3 position) {

}
