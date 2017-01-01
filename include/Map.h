#ifndef IMACGL_MAP_H
#define IMACGL_MAP_H

#include <vector>
#include "Model3d.h"
#include "Model3dtext.h"

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

    glm::vec3 start;
    glm::vec3 end;

    Model3d ** map3D;

    int getCase(int i,int j);
    void setCase(int i,int j,int value);

    int getLines() const;
    void setLines(int lines);

    int getColumns() const;
    void setColumns(int columns);

    void initMap3D(Model3dtext* modelTextList);

};


#endif //IMACGL_MAP_H
