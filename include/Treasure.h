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
    Model3d* model3D;

    Treasure();
    Treasure(int id, const std::string &name, const glm::vec3 &position, const std::string &description);

    int getGold();
    void setGold(int gold);

    Equipment getReward();
    void setReward(Equipment reward);

    void initModel(Model3dtext* modelTextList);


};


#endif //IMACGL_TREASURE_H
