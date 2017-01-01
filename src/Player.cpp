#include "../include/Player.h"

Player::Player() {
    this->camera = new Camera();
}

Player::Player(int id, const std::string &name, const glm::vec3 &position, const std::string &description) : Entity(
        id, name, position, description) {

}

void Player::rotateUp(float degrees) {
    this->camera->rotateUp(degrees);
}

void Player::rotateLeft(float degrees) {
    this->camera->rotateLeft(degrees);

}

void Player::moveFront(float t) {
    this->camera->moveFront(t);
    this->setPosition(this->camera->m_position);
}

void Player::moveLeft(float t) {
    this->camera->moveLeft(t);
    this->setPosition(this->camera->m_position);
}

void Player::moveTo(glm::vec3 position) {
    this->position = position;
    this->camera->m_position = position + glm::vec3(1, 1, 1);

}

glm::vec3 Player::getPosition() {
    return this->camera->m_position - glm::vec3(1, 1, 1);
}


