#ifndef IMACGL_MODEL3DTEXT_H
#define IMACGL_MODEL3DTEXT_H

#include <glimac/Image.hpp>
#include <GL/glew.h>
#include <map>


class model3Dtext {
public:
    std::string text;
    glimac::Image* texture;
    GLuint textureID;

};


class Model3dtext {
public:
    Model3dtext();

    std::map<std::string, model3Dtext> listTextures;

    void addModel3dtexture(std::string text);

    model3Dtext *textureExist(std::string key);
};


#endif //IMACGL_MODEL3DTEXT_H
