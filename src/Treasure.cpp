//
// Created by Quentin on 14/12/2016.
//

#include "../include/Treasure.h"

Treasure::Treasure() {

}

Treasure::Treasure(int id, const std::string &name, const glm::vec3 &position, const std::string &description) : Entity(
        id, name, position, description){

}

int Treasure::getGold() {
    return gold;
}

void Treasure::setGold(int gold) {
    this->gold = gold;
}

Equipment Treasure::getReward() {
    return this->reward;
}

void Treasure::setReward(Equipment reward) {
    this->reward = reward;
}



