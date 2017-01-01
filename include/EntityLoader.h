#ifndef IMACGL_ENTITYLOADER_H
#define IMACGL_ENTITYLOADER_H

#include "check.h"
#include "error.h"
#include "GameManager.h"


using namespace tinyxml2;


class EntityLoader {
public:
    static void loadEntities(GameManager& gm,const char *path );

};


#endif //IMACGL_ENTITYLOADER_H
