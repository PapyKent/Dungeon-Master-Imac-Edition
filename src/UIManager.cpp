//
// Created by Quentin on 14/12/2016.
//

#include "../include/UIManager.h"

void UIManager::initSDL(float largeur, float hauteur, const char *name) {
    this->hauteur = hauteur;
    this->largeur = largeur;
    this->windowManager = new glimac::SDLWindowManager(largeur, hauteur, name);
}
