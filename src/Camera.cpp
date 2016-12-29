//
// Created by Quentin on 28/12/2016.
//

#include "../include/Camera.h"

Camera::Camera() {
    this->m_position = glm::vec3(0,0,0);
    m_fPhi = M_PI;
    m_fTheta = 0;
    computeDirectionVectors();
}

Camera::Camera(glm::vec3 position) {
    this->m_position = position;
    m_fPhi = M_PI;
    m_fTheta = 0;
    computeDirectionVectors();
}


void Camera::computeDirectionVectors(){
    this->m_FrontVector = glm::vec3 (cos(m_fTheta)*sin(m_fPhi),sin(m_fTheta),cos(m_fTheta)*cos(m_fPhi));
    this->m_LeftVector = glm::vec3(sin(m_fPhi+(M_PI/2)),0,cos(m_fPhi+(M_PI/2)));
    this->m_UpVector = glm::cross(m_FrontVector,m_LeftVector);
}

void Camera::moveLeft(float t) {
    this->m_position+= t*m_LeftVector;
    computeDirectionVectors();
}

void Camera::moveFront(float t) {
    this->m_position+= t*m_FrontVector;
    computeDirectionVectors();
}

void Camera::rotateLeft(float degrees) {
    float rad = toolBox::convertDegToRad(degrees);
    m_fPhi+=rad;
    computeDirectionVectors();
}

void Camera::rotateUp(float degrees) {
    float rad = toolBox::convertDegToRad(degrees);
    m_fTheta+=rad;
    computeDirectionVectors();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(m_position,m_position+m_FrontVector,m_UpVector);
}


