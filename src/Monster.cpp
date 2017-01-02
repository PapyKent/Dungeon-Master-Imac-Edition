#include "../include/Monster.h"

Monster::Monster() {

}

Monster::Monster(int id, const std::string &name, const glm::vec3 &position, const std::string &description) : Entity(
        id, name, position, description) {

}

void Monster::moveTo(glm::vec3 position) {

}

std::string Monster::getWeakness() {
    return weakness;
}

void Monster::setWeakness(const std::string &weakness) {
    this->weakness = weakness;
}

std::string Monster::getResistance() {
    return resistance;
}

void Monster::setResistance(std::string resistance) {
    this->resistance = resistance;
}

std::string Monster::getType() {
    return type;
}

void Monster::setType(const std::string type) {
    this->type = type;
}

int Monster::getAtk() {
    return atk;
}

void Monster::setAtk(int atk) {
    this->atk = atk;
}

int Monster::getDef() {
    return def;
}

void Monster::setDef(int def) {
    this->def = def;
}

int Monster::getLife() {
    return life;
}

void Monster::setLife(int life) {
    this->life = life;
}

void Monster::initModel(Model3dtext *modelTextList) {
    this->model3D = new Model3d;
    this->model3D->model = this->model;
    this->model3D->text = this->text;
    this->model3D->position = this->position+(glm::vec3(1,0,1));
    this->model3D->initModel("nomShader", modelTextList);
}

