//
// Created by Quentin on 14/12/2016.
//

#ifndef IMACGL_DRAW_H
#define IMACGL_DRAW_H

#include <glimac/SDLWindowManager.hpp>

class UIManager {
public:
    float largeur;
    float hauteur;
    glimac::SDLWindowManager *windowManager;

    void initSDL(float largeur, float hauteur, const char* name);
};


#endif //IMACGL_DRAW_H
