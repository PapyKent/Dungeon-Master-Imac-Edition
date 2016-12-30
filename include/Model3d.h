//
// Created by Quentin on 30/12/2016.
//

#ifndef IMACGL_MODEL3D_H
#define IMACGL_MODEL3D_H

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <GL/glew.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL/SDL.h>
#include <string>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/Geometry.hpp>

class Model3d {
public:
    Model3d();
    ~Model3d();
    glm::vec3 position;
    std::string model;
    std::string text;
    glimac::Program program ;

    //modele 3D
    glimac::Geometry geometry;

    //texture
    std::unique_ptr<glimac::Image> texture;
    GLuint * textureID;

    //
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXCORD = 2;

    glm::mat4 ProjMatrix;
    glm::mat4 MVMatrix;
    glm::mat4 NormalMatrix;

    GLint  uMVPMatrixLoc;
    GLint  uMVMatrixLoc;
    GLint  uNormalMatrixLoc;

    GLuint vbo;
    GLuint vao;

    void initModel();
    void initGeometry();
    int initGlew();
    void initProgram(std::string path);
    void draw(glm::mat4 viewMatrix);

    void freeRessources();
};


#endif //IMACGL_MODEL3D_H