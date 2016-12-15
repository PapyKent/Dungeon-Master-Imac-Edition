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
    std::map<std::string,std::string> weaknesses;
    std::map<std::string,std::string> resistances;
    std::string type;
    int atk;
    int def;
    int life;
    //modele 3D


public:
    Monster();
    Monster(int id, const std::string &name, const glm::vec3 &position, const std::string &description);
    void moveTo(glm::vec3 position);

    std::map<std::string, std::string> getWeaknesses();

    void setWeaknesses(const std::map<std::string, std::string> &weaknesses);

    std::map<std::string, std::string> getResistances();

    void setResistances(const std::map<std::string, std::string> &resistances);

    std::string getType();

    void setType(const std::string &type);

    int getAtk();

    void setAtk(int atk);

    int getDef();

    void setDef(int def);

    int getLife();

    void setLife(int life);



};


#endif //IMACGL_MONSTER_H
