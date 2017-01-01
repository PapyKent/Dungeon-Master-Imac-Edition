#include "../include/Treasure.h"

Treasure::Treasure() {

}

Treasure::Treasure(int id, const std::string &name, const glm::vec3 &position, const std::string &description) : Entity(
        id, name, position, description) {

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

void Treasure::initModel(Model3dtext *modelTextList) {
    this->model3D = new Model3d;
    this->model3D->model = this->model;
    this->model3D->text = this->text;
    this->model3D->position = this->position;
    this->model3D->initModel("nomShader", modelTextList);
}




