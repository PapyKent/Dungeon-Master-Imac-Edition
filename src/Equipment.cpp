//
// Created by Quentin on 14/12/2016.
//

#include "../include/Equipment.h"



int Equipment::getAtk(){
    return atk;
}

void Equipment::setAtk(int atk) {
    this->atk = atk;
}

int Equipment::getDef(){
    return def;
}

void Equipment::setDef(int def) {
    this->def = def;
}

string Equipment::getDamageType(){
    return this->damageType;
}

void Equipment::setDamageType(std::string damageType) {
    this->damageType = damageType;
}
