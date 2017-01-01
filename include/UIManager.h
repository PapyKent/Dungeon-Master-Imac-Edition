#ifndef IMACGL_DRAW_H
#define IMACGL_DRAW_H

#define GLEW_STATIC

#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL/SDL.h>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/Geometry.hpp>
#include "GameManager.h"

class UIManager {
public:
    float largeur;
    float hauteur;
    glimac::SDLWindowManager *windowManager;

    UIManager();

    void initSDL(float largeur, float hauteur, const char* name);
    int initGlew();
    void render(GameManager* gm);
    void updateDisplay();

};


#endif //IMACGL_DRAW_H
