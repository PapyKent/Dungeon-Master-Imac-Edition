#include "../include/GameManager.h"

GameManager::GameManager() {
    this->player = new Player();
    button = false;
    std::srand(time(NULL));
    isFighting = false;
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

bool GameManager::eventManager(SDL_Event &event) {
    int angleRot = 90;
    int pas = 2;
    bool atk = false;
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
                    if (!isFighting) {
                        if (canMoveFront(pas)) {
                            this->player->moveFront(pas);
                            moveEnnemies(pas);
                        }
                    }
                    break;
                case SDLK_s:
                    if (!isFighting) {
                        if (canMoveFront(-pas)) {
                            this->player->moveFront(-pas);
                            moveEnnemies(pas);
                        }
                    }
                    break;
                case SDLK_a:
                    if (!isFighting) {
                        if (canMoveLeft(pas)) {
                            this->player->moveLeft(pas);
                            moveEnnemies(pas);
                        }
                    }

                    break;
                case SDLK_d:
                    if (!isFighting) {
                        if (canMoveLeft(-pas)) {
                            this->player->moveLeft(-pas);
                            moveEnnemies(pas);
                        }
                    }
                    break;

                case SDLK_SPACE:
                    atk = true;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

    checkTreasure(pas, atk);

    isFighting = checkFight(pas, atk);
    if (player->life <= 0) {
        player->life = 10;
        player->moveTo(map->start);
    }
    return checkFinish();
}

bool GameManager::getStatut() const {
    return statut;
}

void GameManager::setStatut(bool s) {
    this->statut = s;
}

void GameManager::initEntities3d(Model3dtext *modelTextList) {
    for (int i = 0; i < this->treasureList.size(); i++) {
        Treasure *t = &this->treasureList[i];
        t->initModel(modelTextList);
    }

    for (int i = 0; i < this->monsterList.size(); i++) {
        Monster *t = &this->monsterList[i];
        t->initModel(modelTextList);
    }

    for (int i = 0; i < this->equipmentList.size(); i++) {
        Equipment *t = &this->equipmentList[i];
        t->initModel(modelTextList);
    }
}

bool GameManager::checkFinish() {
    int x = round(this->player->getPosition().x);
    int z = round(this->player->getPosition().z);

    int Fx = round(this->map->end.x);
    int Fz = round(this->map->end.z);

    return x == Fx && z == Fz;
}

bool GameManager::canMoveFront(float t) {
    glm::vec3 futurPos = this->player->getPosition() + (this->player->camera->m_FrontVector * t);
    int futX = round(futurPos.x / 2);
    int futZ = round(futurPos.z / 2);
    if (futX < this->map->getColumns() && futX >= 0 && futZ < this->map->getLines() && futZ >= 0)
        if (map->getCase(futX, futZ) != 3)
            return true;
    return false;
}

bool GameManager::canMoveLeft(float t) {
    glm::vec3 futurPos = this->player->getPosition() + (this->player->camera->m_LeftVector * t);
    int futX = round(futurPos.x / 2);
    int futZ = round(futurPos.z / 2);
    if (futX < this->map->getColumns() && futX >= 0 && futZ < this->map->getLines() && futZ >= 0)
        if (map->getCase(futX, futZ) != 3)
            return true;
    return false;
}

void GameManager::moveEnnemies(float pas) {
    glm::vec3 FrontVector(0, 0, -1);
    glm::vec3 LeftVector(-1, 0, 0);
    for (int i = 0; i < this->monsterList.size(); i++) {
        Monster *monster = &this->monsterList[i];
        int choice = std::rand() % 4 + 1;
        glm::vec3 futurPos;
        int futX;
        int futZ;
        switch (choice) {
            case 1://up
            {
                futurPos = monster->getPosition() + (FrontVector * pas);
                futX = round(futurPos.x / 2);
                futZ = round(futurPos.z / 2);
                if (futX < this->map->getColumns() && futX >= 0 && futZ < this->map->getLines() && futZ >= 0) {
                    if (map->getCase(futX, futZ) != 3) {
                        if (glm::distance(futurPos, this->player->getPosition()) > 2) {
                            monster->setPosition(futurPos);
                            monster->model3D->position = futurPos + glm::vec3(1, 0, 1);
                        }
                    }
                }
                break;
            }

            case 2://down
            {
                futurPos = monster->getPosition() + (FrontVector * -pas);
                futX = round(futurPos.x / 2);
                futZ = round(futurPos.z / 2);
                if (futX < this->map->getColumns() && futX >= 0 && futZ < this->map->getLines() && futZ >= 0)
                    if (map->getCase(futX, futZ) != 3) {
                        if (glm::distance(futurPos, this->player->getPosition()) > 2) {
                            monster->setPosition(futurPos);
                            monster->model3D->position = futurPos + glm::vec3(1, 0, 1);
                        }
                    }
                break;
            }
            case 3://left
            {
                futurPos = monster->getPosition() + (LeftVector * pas);
                futX = round(futurPos.x / 2);
                futZ = round(futurPos.z / 2);
                if (futX < this->map->getColumns() && futX >= 0 && futZ < this->map->getLines() && futZ >= 0)
                    if (map->getCase(futX, futZ) != 3) {
                        if (glm::distance(futurPos, this->player->getPosition()) > 2) {
                            monster->setPosition(futurPos);
                            monster->model3D->position = futurPos + glm::vec3(1, 0, 1);
                        }
                    }
                break;
            }
            case 4://right
            {
                futurPos = monster->getPosition() + (LeftVector * -pas);
                futX = round(futurPos.x / 2);
                futZ = round(futurPos.z / 2);
                if (futX < this->map->getColumns() && futX >= 0 && futZ < this->map->getLines() && futZ >= 0)
                    if (map->getCase(futX, futZ) != 3) {
                        if (glm::distance(futurPos, this->player->getPosition()) > 2) {
                            monster->setPosition(futurPos);
                            monster->model3D->position = futurPos + glm::vec3(1, 0, 1);
                        }
                    }
                break;
            }
            default:
                break;

        }
    }


}

bool GameManager::checkFight(float pas, bool atk) {
    for (int i = 0; i < this->monsterList.size(); i++) {
        Monster *monster = &this->monsterList[i];
        if (glm::distance(this->player->getPosition(), monster->getPosition()) < pas * 2) {
            if (atk)
                fight(monster);
            return true;
        }
    }

    return false;
}


bool GameManager::checkTreasure(float pas, bool action) {
    for (int i = 0; i < this->treasureList.size(); i++) {
        Treasure *treasure = &this->treasureList[i];
        if (glm::distance(this->player->getPosition(), treasure->getPosition()) < pas * 2) {
            if (action)
                getTreasure(treasure);
            return true;
        }
    }

    return false;
}

void GameManager::fight(Monster *monster) {
    //hit
    monster->setLife(monster->getLife() - 1);
    //get hit
    if (monster->getLife() > 0)
        this->player->life -= 2;
    else
        removeMonster(monster->getId());
}

void GameManager::getTreasure(Treasure *treasure) {
    this->player->life += 5;
    removeTreasure(treasure->getId());
}










