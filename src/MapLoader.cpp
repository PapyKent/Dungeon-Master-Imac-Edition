//
// Created by Quentin on 14/12/2016.
//

#include "../include/MapLoader.h"


void MapLoader::loadMap(){

    //FILE * ppmFile;
    //ppmFile = fopen("../../assets//ppm/lab.ppm", "r");

    fstream ppmFile("../../assets//ppm/lab.ppm", ios::in);

    //if(ppmFile != NULL){

    if(ppmFile){

        int i = 0;

        string type, version, colonnes, lignes, borne, data;

        getline(ppmFile,type);
        cout << type << endl;

        getline(ppmFile,version);
        cout << version << endl;

        getline(ppmFile,colonnes, ' ');
        int colonnesI = stoi(colonnes);
        cout << colonnesI << endl;

        getline(ppmFile,lignes);
        int lignesI = stoi(lignes);
        cout << lignesI << endl;

        getline(ppmFile, borne);
        cout << borne << endl;

        int mat[colonnesI*lignesI*3];

        for(int i = 0; i < colonnesI*lignesI*3 ; i++){
            getline(ppmFile, data);

            mat[i] = stoi(data);
        }

        int r, g, b;
        int map[colonnesI][lignesI];

        for(int i = 0; i < colonnesI*lignesI*3 ; i+=3){

            r = mat[i];
            g = mat[i+1];
            b = mat[i+2];

            if(r == 184 && g == 20 && b == 20){
                //cout << "Start" << endl;
                map[(i/3)%colonnesI][(i/3)/lignesI] = 1;
            }
            if(r == 66 && g == 198 && b == 59){
                //cout << "End" << endl;
                map[(i/3)%colonnesI][(i/3)/lignesI] = 2;
            }
            if(r == 0 && g == 0 && b == 0){
                //cout << "Wall" << endl;
                map[(i/3)%colonnesI][(i/3)/lignesI] = 3;
            }
            if(r == 255 && g == 255 && b == 255){
                //cout << "Corridor" << endl;
                map[(i/3)%colonnesI][(i/3)/lignesI] = 4;
            }

            cout << map[(i/3)%colonnesI][(i/3)/lignesI] << endl ;
        }



        for(int i = 0; i < colonnesI; i++){
            for(int j = 0 ; j < lignesI; j++){

            }
        }

    }
    else{
        cout << "Impossible d'ouvrir le fichier" << endl;
    }


}
