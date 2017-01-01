#include "../include/UIManager.h"


UIManager::UIManager() {


}

void UIManager::initSDL(float largeur, float hauteur, const char *name) {
    this->hauteur = hauteur;
    this->largeur = largeur;
    this->windowManager = new glimac::SDLWindowManager(largeur, hauteur, name);
    SDL_EnableUNICODE(1);
}

int UIManager::initGlew() {
    GLenum glewInitError = glewInit();
    if (GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return 1;
    }
}


void UIManager::render(GameManager *gm) {

    /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/


    //Nettoyer la fenetre, para indique ce qu'il faut nettoyer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < gm->map->getColumns(); i++) {
        for (int j = 0; j < gm->map->getLines(); j++) {
            gm->map->map3D[i][j].draw(gm->player->camera->getViewMatrix(), gm->player->getPosition());
        }
    }

    for (int i = 0; i < gm->monsterList.size(); i++) {
        gm->monsterList[i].model3D->draw(gm->player->camera->getViewMatrix(), gm->player->getPosition());
    }

    for (int i = 0; i < gm->treasureList.size(); i++) {
        gm->treasureList[i].model3D->draw(gm->player->camera->getViewMatrix(), gm->player->getPosition());
    }


}

void UIManager::updateDisplay() {
    windowManager->swapBuffers();
}
