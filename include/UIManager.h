//
// Created by Quentin on 14/12/2016.
//

#ifndef IMACGL_DRAW_H
#define IMACGL_DRAW_H

#define GLEW_STATIC

#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <string>
#include <SDL/SDL.h>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>

class UIManager {
public:
    float largeur;
    float hauteur;
    glimac::SDLWindowManager *windowManager;

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXCORD = 2;

    GLuint vbo;
    GLuint vao;

    GLint  uMVPMatrixLoc;
    GLint  uMVMatrixLoc;
    GLint  uNormalMatrixLoc;

    glimac::Sphere* sphere;
    glm::mat4 ProjMatrix;
    glm::mat4 MVMatrix;
    glm::mat4 NormalMatrix;

    UIManager();

    void initSDL(float largeur, float hauteur, const char* name);
    int initGlew();
    void loadShaders( glimac::Program &program, char **argv);
    void initOpenGL(glimac::Program &program);
    void render(glm::mat4 viewMatrix);
    void updateDisplay();
    void freeRessources();
};


#endif //IMACGL_DRAW_H
