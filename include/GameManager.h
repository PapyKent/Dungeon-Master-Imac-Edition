#ifndef IMACGL_GAMEMANAGER_H
#define IMACGL_GAMEMANAGER_H
#include <vector>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <time.h>

#include "Monster.h"
#include "Treasure.h"
#include "Map.h"
#include "Player.h"
#include "Model3dtext.h"


class GameManager {
private:

    std::string ppmFile;
    std::string gameName;
    bool statut;
    bool button;


public:
    Map *map;
    std::vector<Monster> monsterList;
    std::vector<Treasure> treasureList;
    std::vector<Equipment> equipmentList;

    GameManager();
    Player* player;
    bool isFighting;



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


    bool eventManager(SDL_Event &e);
    bool checkFinish();
    bool canMoveFront(float t);
    bool canMoveLeft(float t);

    void moveEnnemies(float pas);

    bool getStatut() const;

    void setStatut(bool jeu);

    void initEntities3d(Model3dtext* modelTextList);

    bool checkFight(float pas, bool atk);

    void fight( Monster *monster);

    bool checkTreasure(float pas, bool action);

    void getTreasure(Treasure *treasure);

};


#endif //IMACGL_GAMEMANAGER_H
