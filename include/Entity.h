//
// Created by Quentin on 14/12/2016.
//

#ifndef IMACGL_ENTITY_H
#define IMACGL_ENTITY_H

#include <glimac/glm.hpp>
#include <string>

class Entity {
private:
    int id;
    std::string name;
    glm::vec3 position;
    std::string description;
    std::string model;

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

};


#endif //IMACGL_ENTITY_H
