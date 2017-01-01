#include "../include/Map.h"

Map::Map() {

}

Map::Map(int i, int j) {
    columns = i;
    lines = j;
    map = new int *[columns];
    for (int i = 0; i < columns; i++)
        map[i] = new int[lines];

}

int Map::getCase(int i, int j) {
    return this->map[i][j];

}

void Map::setCase(int i, int j, int value) {
    this->map[i][j] = value;
}

Map::~Map() {
    for (int i = 0; i < columns; i++)
        delete[] map[i];
    delete[] map;

    for (int i = 0; i < columns; i++)
        delete[] map3D[i];
    delete[] map3D;

}

int Map::getLines() const {
    return lines;
}

void Map::setLines(int lines) {
    Map::lines = lines;
}

int Map::getColumns() const {
    return columns;
}

void Map::setColumns(int columns) {
    Map::columns = columns;
}

void Map::initMap3D(Model3dtext *modelTextList) {
    map3D = new Model3d *[columns];
    for (int i = 0; i < columns; i++)
        map3D[i] = new Model3d[lines];

    int cube_size = 2;
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < lines; j++) {
            map3D[i][j].model = "Cube";
            switch (map[i][j]) {
                case 1 :
                    map3D[i][j].text = "ground2_exit2";
                    map3D[i][j].position = glm::vec3(i * cube_size, -cube_size, j * cube_size);
                    map3D[i][j].initModel("cube", modelTextList);
                    this->start = glm::vec3(i * cube_size, 0, j * cube_size);
                    break;
                case 2 :
                    map3D[i][j].text = "ground2_exit";
                    map3D[i][j].initModel("cube", modelTextList);
                    map3D[i][j].position = glm::vec3(i * cube_size, -cube_size, j * cube_size);
                    this->end = glm::vec3(i * cube_size, 0, j * cube_size);
                    break;
                case 3 :
                    map3D[i][j].text = "wall2";
                    map3D[i][j].initModel("cube", modelTextList);
                    map3D[i][j].position = glm::vec3(i * cube_size, 0, j * cube_size);
                    break;
                case 4 :
                    map3D[i][j].text = "ground2";
                    map3D[i][j].initModel("cube", modelTextList);
                    map3D[i][j].position = glm::vec3(i * cube_size, -cube_size, j * cube_size);
                    break;


                default:
                    break;
            }


        }
    }
}
