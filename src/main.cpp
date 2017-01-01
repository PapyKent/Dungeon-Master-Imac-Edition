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
#include "../include/Model3d.h"


using namespace glimac;

void addModel3dtexture(string text);
Model3dtext* textureExist(string text);




int main(int argc, char **argv) {

    GameManager gm;
    EntityLoader::loadEntities(gm,"../../files/xml/game.xml");
    Model3dtext modelTextList;
    MapLoader::loadMap(gm);

    float largeur = 800;
    float hauteur = 800;



    UIManager uim;
    // Initialize SDL and open a window
    uim.initSDL(largeur,hauteur,gm.getGameName().c_str());
    // Initialize glew for OpenGL3+ support
    uim.initGlew();

    gm.map->initMap3D(&modelTextList);
    gm.player->moveTo(gm.map->start);
    gm.initEntities3d(&modelTextList);


    // Application loop:
    bool done = false;

    while (!gm.getStatut() && !done) {
        // Event loop:
        SDL_Event e;
        while (uim.windowManager->pollEvent(e)) {
            done = gm.eventManager(e);
        }
        // render code
        uim.render(&gm);
        // Update the display
        uim.updateDisplay();
    }


    return 0;
}



