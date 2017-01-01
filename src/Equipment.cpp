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

void Equipment::initModel(Model3dtext* modelTextList) {
    this->model3D = new Model3d;
    this->model3D->model = this->model;
    this->model3D->text = this->text;
    this->model3D->position = this->position;
    this->model3D->initModel("nomShader",modelTextList);
}