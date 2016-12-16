//
// Created by Quentin on 14/12/2016.
//

#include "../include/Map.h"

Map::Map() {

}

Map::Map(int i, int j) {
    columns = i;
    lines = j;
    map = new int*[columns];
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
