//
// Created by Quentin on 28/12/2016.
//

#ifndef IMACGL_CAMERA_H
#define IMACGL_CAMERA_H


#include "toolBox.h"
#include <glimac/glm.hpp>
#include <math.h>

class Camera {
public:
    glm::vec3 m_position;
    float m_fPhi;
    float m_fTheta;
    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;

    Camera();
    Camera(glm::vec3 position);

    void computeDirectionVectors();
    void moveLeft(float t);
    void moveFront(float t);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    glm::mat4 getViewMatrix();

};


#endif //IMACGL_CAMERA_H
