//
// Created by Quentin on 14/12/2016.
//

#include "../include/Monster.h"

Monster::Monster() {

}

Monster::Monster(int id, const std::string &name, const glm::vec3 &position, const std::string &description) : Entity(
        id, name, position, description) {

}

void Monster::moveTo(glm::vec3 position) {

}

std::map<std::string, std::string> Monster::getWeaknesses(){
    return weaknesses;
}

void Monster::setWeaknesses(const std::map<std::string, std::string> &weaknesses) {
    this->weaknesses = weaknesses;
}

std::map<std::string, std::string> Monster::getResistances(){
    return resistances;
}

void Monster::setResistances(const std::map<std::string, std::string> &resistances) {
    this->resistances = resistances;
}

std::string Monster::getType(){
    return type;
}

void Monster::setType(const std::string &type) {
    this->type = type;
}

int Monster::getAtk(){
    return atk;
}

void Monster::setAtk(int atk) {
    this->atk = atk;
}

int Monster::getDef(){
    return def;
}

void Monster::setDef(int def) {
    this->def = def;
}

int Monster::getLife(){
    return life;
}

void Monster::setLife(int life) {
    this->life = life;
}


