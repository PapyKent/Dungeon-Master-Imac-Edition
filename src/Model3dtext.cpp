#include "../include/Model3dtext.h"

Model3dtext::Model3dtext() {

}


void Model3dtext::addModel3dtexture(std::string text) {
    model3Dtext m;
    m.text = text;
    m.texture = glimac::loadImage("../../assets/textures/" + text + ".png").get();
    glGenTextures(1, &m.textureID);

    std::pair<std::string, model3Dtext> tmp(m.text, m);
    listTextures.insert(tmp);
}

model3Dtext *Model3dtext::textureExist(std::string key) {
    if (listTextures.find(key) != listTextures.end()) { //iterator check
        return &(listTextures[key]);
    } else
        return NULL;
}

