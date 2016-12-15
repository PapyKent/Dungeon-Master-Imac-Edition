//
// Created by Quentin on 14/12/2016.
//

#include "../include/Entity.h"

Entity::Entity() {

}

Entity::Entity(int id, std::string name, glm::vec3 position, std::string description)
        : id(id), name(name), position(position), description(description) {

}

int Entity::getId(){
    return id;
}

void Entity::setId(int id) {
    this->id = id;
}

std::string Entity::getName(){
    return name;
}

void Entity::setName(const std::string &name) {
    this->name = name;
}

glm::vec3 Entity::getPosition(){
    return position;
}

void Entity::setPosition(const glm::vec3 &position) {
    this->position = position;
}

std::string Entity::getDescription(){
    return description;
}

void Entity::setDescription(const std::string &description) {
    this->description = description;
}




