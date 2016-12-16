//
// Created by Quentin on 14/12/2016.
//

#ifndef IMACGL_TREASURE_H
#define IMACGL_TREASURE_H

#include "Entity.h"
#include "Equipment.h"
#include <string>



class Treasure : public Entity {
private:
    Equipment reward;
    int gold;

public:
    Treasure();
    Treasure(int id, const std::string &name, const glm::vec3 &position, const std::string &description);

    int getGold();
    void setGold(int gold);

    Equipment getReward();
    void setReward(Equipment reward);

    

};


#endif //IMACGL_TREASURE_H
