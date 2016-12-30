//
// Created by Quentin on 14/12/2016.
//

#include <iostream>
#include "../include/GameManager.h"

GameManager::GameManager() {
    this->player = new Player();
    button = false;
}

void GameManager::addMonster(Monster m) {
    this->monsterList.push_back(m);
}

void GameManager::addTreasure(Treasure t) {
    this->treasureList.push_back(t);
}

void GameManager::addEquipment(Equipment e) {
    this->equipmentList.push_back(e);
}

void GameManager::removeMonster(int id) {
    for (std::vector<Monster>::iterator it = this->monsterList.begin(); it != this->monsterList.end(); it++) {
        if (it->getId() == id) {
            this->monsterList.erase(it);
            return;
        }
    }
}

void GameManager::removeTreasure(int id) {
    for (std::vector<Treasure>::iterator it = this->treasureList.begin(); it != this->treasureList.end(); it++) {
        if (it->getId() == id) {
            this->treasureList.erase(it);
            return;
        }
    }
}

void GameManager::removeEquipment(int id) {
    for (std::vector<Equipment>::iterator it = this->equipmentList.begin(); it != this->equipmentList.end(); it++) {
        if (it->getId() == id) {
            this->equipmentList.erase(it);
            return;
        }
    }
}

std::string GameManager::getPpmFile() {
    return ppmFile;
}

void GameManager::setPpmFile(const std::string &ppmFile) {
    this->ppmFile = ppmFile;
}

std::string GameManager::getGameName() {
    return gameName;
}

void GameManager::setGameName(const std::string &gameName) {
    this->gameName = gameName;
}

bool GameManager::findMonster(int id, Monster &m) {
    for (std::vector<Monster>::iterator it = this->monsterList.begin(); it != this->monsterList.end(); it++) {
        if (it->getId() == id) {
            m = *it;
            return true;
        }
    }
    return false;
}

bool GameManager::findTreasure(int id, Treasure &t) {
    for (std::vector<Treasure>::iterator it = this->treasureList.begin(); it != this->treasureList.end(); it++) {
        if (it->getId() == id) {
            t = *it;
            return true;
        }
    }
    return false;
}

bool GameManager::findEquipment(int id, Equipment &e) {
    for (std::vector<Equipment>::iterator it = this->equipmentList.begin(); it != this->equipmentList.end(); it++) {
        if (it->getId() == id) {
            e = *it;
            return true;
        }
    }
    return false;
}

void GameManager::eventManager(SDL_Event &event) {
    int angleRot = 90;
    int pas = 2;
    switch (event.type) {
        case SDL_QUIT:
            this->statut = true;
            break;
        case SDL_KEYUP:

            switch (event.key.keysym.sym) {
                case SDLK_q:
                    this->player->rotateLeft(angleRot);
                    break;
                case SDLK_e:
                    this->player->rotateLeft(-angleRot);
                    break;
                case SDLK_w:
                    this->player->moveFront(pas);
                    break;
                case SDLK_s:
                    this->player->moveFront(-pas);
                    break;
                case SDLK_a:
                    this->player->moveLeft(pas);
                    break;
                case SDLK_d:
                    this->player->moveLeft(-pas);
                    break;
                default:
                    break;
            }
            break;

        default:
            break;

    }


}

bool GameManager::getStatut() const {
    return statut;
}

void GameManager::setStatut(bool s) {
    this->statut = s;
}




