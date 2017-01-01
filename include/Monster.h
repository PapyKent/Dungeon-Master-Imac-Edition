//
// Created by Quentin on 14/12/2016.
//

#ifndef IMACGL_MONSTER_H
#define IMACGL_MONSTER_H

#include "Entity.h"
#include <map>
#include <string>

#include <glimac/Sphere.hpp>


class Monster : public Entity{
private:
    std::string weakness;
    std::string resistance;
    std::string type;
    int atk;
    int def;
    int life;



public:
    Model3d* model3D;

    Monster();
    Monster(int id, const std::string &name, const glm::vec3 &position, const std::string &description);
    void moveTo(glm::vec3 position);

    std::string getWeakness();

    void setWeakness(const std::string &weaknesses);

    std::string getResistance();

    void setResistance(const std::string resistances);

    std::string getType();

    void setType(const std::string type);

    int getAtk();

    void setAtk(int atk);

    int getDef();

    void setDef(int def);

    int getLife();

    void setLife(int life);
    void initModel();



};


#endif //IMACGL_MONSTER_H
