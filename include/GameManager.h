//
// Created by Quentin on 14/12/2016.
//

#ifndef IMACGL_GAMEMANAGER_H
#define IMACGL_GAMEMANAGER_H
#include <vector>
#include <SDL/SDL.h>

#include "monster.h"
#include "treasure.h"
#include "Map.h"
#include "Player.h"


class GameManager {
private:
    std::vector<Monster> monsterList;
    std::vector<Treasure> treasureList;
    std::vector<Equipment> equipmentList;

    std::string ppmFile;
    std::string gameName;
    bool statut;
    bool button;


public:
    Map *map;
    GameManager();
    Player* player;

    void addMonster(Monster m);
    void addTreasure(Treasure t);
    void addEquipment(Equipment e);

    void removeMonster(int id);
    void removeTreasure(int id);
    void removeEquipment(int id);

    bool findMonster(int id,Monster& m);
    bool findTreasure(int id,Treasure& m);
    bool findEquipment(int id,Equipment& m);

    std::string getPpmFile();

    void setPpmFile(const std::string &ppmFile);

    std::string getGameName();

    void setGameName(const std::string &gameName);


    void eventManager(SDL_Event &e);

    bool getStatut() const;

    void setStatut(bool jeu);

};


#endif //IMACGL_GAMEMANAGER_H
