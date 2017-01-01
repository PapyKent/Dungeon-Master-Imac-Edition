//
// Created by Quentin on 14/12/2016.
//

#ifndef IMACGL_EQUIPMENT_H
#define IMACGL_EQUIPMENT_H

#include <string>

#include "Entity.h"

using namespace std;

class Equipment : public Entity{
private:
    int atk;
    int def;
    string damageType;

public:
    Model3d* model3D;

    int getAtk();
    void setAtk(int atk);

    int getDef();
    void setDef(int def);

    string getDamageType();
    void setDamageType(string damageType);
    void initModel();


};


#endif //IMACGL_EQUIPMENT_H
