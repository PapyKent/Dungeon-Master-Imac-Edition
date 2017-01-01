#ifndef IMACGL_ENTITY_H
#define IMACGL_ENTITY_H

#include <glimac/glm.hpp>
#include <string>
#include "Model3d.h"

class Entity {
protected:
    int id;
    std::string name;
    glm::vec3 position;
    std::string description;
    std::string model;
    std::string text;

public :

    Entity();
    Entity(int id, std::string name, glm::vec3 position, std::string description);

    int getId();
    void setId(int id);

    std::string getName();
    void setName(const std::string &name);

    glm::vec3 getPosition();
    void setPosition(const glm::vec3 &position);

    std::string getDescription();
    void setDescription(const std::string &description);

    std::string getModel();
    void setModel(const std::string &model);

    std::string getText();
    void setText(const std::string &text);
};


#endif //IMACGL_ENTITY_H
