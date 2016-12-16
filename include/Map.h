//
// Created by Quentin on 14/12/2016.
//

#ifndef IMACGL_MAP_H
#define IMACGL_MAP_H

#include <vector>

using namespace std;

class Map {
private:
    int lines;
    int columns;
    int ** map;

public:
    Map();
    Map(int i,int j);
    ~Map();

    int getCase(int i,int j);
    void setCase(int i,int j,int value);

    int getLines() const;
    void setLines(int lines);

    int getColumns() const;
    void setColumns(int columns);


};


#endif //IMACGL_MAP_H
