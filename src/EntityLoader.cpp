//
// Created by Quentin on 14/12/2016.
//

#include "../include/EntityLoader.h"


void EntityLoader::loadEntities(GameManager& gm,const char *path) {
    XMLDocument doc;
    doc.LoadFile(path);

    XMLNode *docRoot = NULL;
    if (!Check::isFileNull(&doc, path)) {
        docRoot = doc.FirstChild();
    }

    if (!Check::isElementNull(docRoot, "gameName")) {
        gm.setGameName(docRoot->FirstChildElement("gameName")->GetText());
    }

    if (!Check::isElementNull(docRoot, "ppm")) {
        gm.setPpmFile(docRoot->FirstChildElement("ppm")->GetText());
    }

    XMLElement *docMonsters;

    if (!Check::isElementNull(docRoot, "monster")) {
        docMonsters = docRoot->FirstChildElement("monster");
    }

    //parcours monstres
    while (docMonsters != NULL) {
        Monster monster;
        if (Check::isTypeCorrect(docMonsters->FirstChildElement("id"))) {
            int id = stoi(docMonsters->FirstChildElement("id")->GetText());
            //check if number
            monster.setId(id);
        }

        if (!Check::isElementNull(docMonsters, "name")) {
            monster.setName(docMonsters->FirstChildElement("name")->GetText());
        }

        if (!Check::isElementNull(docMonsters, "description")) {
            monster.setDescription(docMonsters->FirstChildElement("description")->GetText());
        }

        glm::vec3 position;

        if (Check::isTypeCorrect(docMonsters->FirstChildElement("posX"))) {
            int x = stoi(docMonsters->FirstChildElement("posX")->GetText());
            //check if number
            position.x = x;
        }
        if (Check::isTypeCorrect(docMonsters->FirstChildElement("posY"))) {
            int y = stoi(docMonsters->FirstChildElement("posY")->GetText());
            //check if number
            position.y = y;
        }
        if (Check::isTypeCorrect(docMonsters->FirstChildElement("posZ"))) {
            int z = stoi(docMonsters->FirstChildElement("posZ")->GetText());
            //check if number
            position.z = z;
        }

        monster.setPosition(position);

        if (Check::isTypeCorrect(docMonsters->FirstChildElement("atk"))) {
            int atk = stoi(docMonsters->FirstChildElement("atk")->GetText());
            //check if number
            monster.setAtk(atk);
        }

        if (Check::isTypeCorrect(docMonsters->FirstChildElement("def"))) {
            int def = stoi(docMonsters->FirstChildElement("def")->GetText());
            //check if number
            monster.setDef(def);
        }

        if (Check::isTypeCorrect(docMonsters->FirstChildElement("life"))) {
            int life = stoi(docMonsters->FirstChildElement("life")->GetText());
            //check if number
            monster.setLife(life);
        }

        if (!Check::isElementNull(docMonsters, "type")) {
            monster.setType(docMonsters->FirstChildElement("type")->GetText());
        }

        if (!Check::isElementNull(docMonsters, "weakness")) {
            monster.setWeakness(docMonsters->FirstChildElement("weakness")->GetText());
        }

        if (!Check::isElementNull(docMonsters, "resistance")) {
            monster.setResistance(docMonsters->FirstChildElement("resistance")->GetText());
        }

        if (!Check::isElementNull(docMonsters, "model")) {
            monster.setModel(docMonsters->FirstChildElement("model")->GetText());
        }

        if (!Check::isElementNull(docMonsters, "text")) {
            monster.setModel(docMonsters->FirstChildElement("text")->GetText());
        }


        gm.addMonster(monster);
        docMonsters = docMonsters->NextSiblingElement("monster");
    }





    XMLElement *docEquipment;

    if (!Check::isElementNull(docRoot, "equipment")) {
        docEquipment = docRoot->FirstChildElement("equipment");
    }

    //parcours monstres
    while (docEquipment != NULL) {
        Equipment equipment;
        if (Check::isTypeCorrect(docEquipment->FirstChildElement("id"))) {
            int id = stoi(docEquipment->FirstChildElement("id")->GetText());
            //check if number
            equipment.setId(id);
        }

        if (!Check::isElementNull(docEquipment, "name")) {
            equipment.setName(docEquipment->FirstChildElement("name")->GetText());
        }

        if (!Check::isElementNull(docEquipment, "description")) {
            equipment.setDescription(docEquipment->FirstChildElement("description")->GetText());
        }


        if (Check::isTypeCorrect(docEquipment->FirstChildElement("atk"))) {
            int atk = stoi(docEquipment->FirstChildElement("atk")->GetText());
            //check if number
            equipment.setAtk(atk);
        }

        if (Check::isTypeCorrect(docEquipment->FirstChildElement("def"))) {
            int def = stoi(docEquipment->FirstChildElement("def")->GetText());
            //check if number
            equipment.setDef(def);
        }


        if (!Check::isElementNull(docEquipment, "type")) {
            equipment.setDamageType(docEquipment->FirstChildElement("type")->GetText());
        }

        if (!Check::isElementNull(docEquipment, "model")) {
            equipment.setModel(docEquipment->FirstChildElement("model")->GetText());
        }

        gm.addEquipment(equipment);
        docEquipment = docEquipment->NextSiblingElement("equipment");
    }


    XMLElement *docTreasures;

    if (!Check::isElementNull(docRoot, "treasure")) {
        docTreasures = docRoot->FirstChildElement("treasure");
    }

    //parcours monstres
    while (docTreasures != NULL) {
        Treasure treasure;
        if (Check::isTypeCorrect(docTreasures->FirstChildElement("id"))) {
            int id = stoi(docTreasures->FirstChildElement("id")->GetText());
            //check if number
            treasure.setId(id);
        }

        if (!Check::isElementNull(docTreasures, "name")) {
            treasure.setName(docTreasures->FirstChildElement("name")->GetText());
        }

        if (!Check::isElementNull(docTreasures, "description")) {
            treasure.setDescription(docTreasures->FirstChildElement("description")->GetText());
        }

        glm::vec3 position;

        if (Check::isTypeCorrect(docTreasures->FirstChildElement("posX"))) {
            int x = stoi(docTreasures->FirstChildElement("posX")->GetText());
            //check if number
            position.x = x;
        }
        if (Check::isTypeCorrect(docTreasures->FirstChildElement("posY"))) {
            int y = stoi(docTreasures->FirstChildElement("posY")->GetText());
            //check if number
            position.y = y;
        }
        if (Check::isTypeCorrect(docTreasures->FirstChildElement("posZ"))) {
            int z = stoi(docTreasures->FirstChildElement("posZ")->GetText());
            //check if number
            position.z = z;
        }

        treasure.setPosition(position);

        if (Check::isTypeCorrect(docTreasures->FirstChildElement("gold"))) {
            int gold = stoi(docTreasures->FirstChildElement("gold")->GetText());
            //check if number
            treasure.setGold(gold);
        }

        if (!Check::isElementNull(docTreasures, "model")) {
            treasure.setModel(docTreasures->FirstChildElement("model")->GetText());
        }

        if (Check::isTypeCorrect(docTreasures->FirstChildElement("idReward"))) {
            int idReward = stoi(docTreasures->FirstChildElement("idReward")->GetText());
            Equipment tmp;
            if(gm.findEquipment(idReward,tmp) != false){
                treasure.setReward(tmp);
            }
        }

        gm.addTreasure(treasure);
        docTreasures = docTreasures->NextSiblingElement("treasure");
    }



    //return XML_SUCCESS;
}
