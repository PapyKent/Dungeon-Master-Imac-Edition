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
#include "../include/GameManager.h"
#include "../include/EntityLoader.h"
#include "../include/MapLoader.h"
#include "../include/UIManager.h"
#include "../include/toolBox.h"

using namespace glimac;

int main(int argc, char **argv) {

    GameManager gm;
    EntityLoader::loadEntities(gm,"../../files/xml/game.xml");

    MapLoader::loadMap(gm);

    float largeur = 800;
    float hauteur = 800;

    UIManager uim;
    // Initialize SDL and open a window
    uim.initSDL(largeur,hauteur,gm.getGameName().c_str());
    // Initialize glew for OpenGL3+ support
    uim.initGlew();


    //charge les shaders que l'on a ajouté dans le dossier shaders
    Program program ;
    uim.loadShaders(program,argv);
    program.use();



    std::unique_ptr<Image> ImE = loadImage("..\\..\\assets\\textures\\EarthMap.jpg");
    std::unique_ptr<Image> ImM = loadImage("..\\..\\assets\\textures\\MoonMap.jpg");

    uim.initOpenGL(program);

    // Application loop:
    bool done = false;

    while (!gm.getStatut()) {
        // Event loop:
        SDL_Event e;
        while (uim.windowManager->pollEvent(e)) {
            gm.eventManager(e);
        }
        // render code
        uim.render(gm.player->camera->getViewMatrix());
        // Update the display
        uim.updateDisplay();
    }
    //liberation des ressources
    uim.freeRessources();

    return 0;
}
