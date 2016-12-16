//
// Created by Quentin on 14/12/2016.
//

#include "../include/MapLoader.h"



void MapLoader::loadMap(GameManager &gm){

    //FILE * ppmFile;
    //ppmFile = fopen("../../assets//ppm/lab.ppm", "r");

    fstream ppmFile(gm.getPpmFile().c_str(), ios::in);

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

        //La bonne structure
        gm.map = Map(colonnesI,lignesI);

         int cpt = 0;

        for(int i = 0; i < colonnesI*lignesI*3 ; i+=3){

            r = mat[i];
            g = mat[i+1];
            b = mat[i+2];

            if(r == 184 && g == 20 && b == 20){
                //cout << "Start" << endl;
                map[(i/3)%colonnesI][(i/3)/lignesI] = 1;
                gm.map.setCase((i/3)%colonnesI,(i/3)/lignesI,1);
                cpt++;
            }
            if(r == 66 && g == 198 && b == 59){
                //cout << "End" << endl;
                map[(i/3)%colonnesI][(i/3)/lignesI] = 2;
                gm.map.setCase((i/3)%colonnesI,(i/3)/lignesI,2);
                cpt++;
            }
            if(r == 0 && g == 0 && b == 0){
                //cout << "Wall" << endl;
                map[(i/3)%colonnesI][(i/3)/lignesI] = 3;
                gm.map.setCase((i/3)%colonnesI,(i/3)/lignesI,3);
                cpt++;
            }
            if(r == 255 && g == 255 && b == 255){
                //cout << "Corridor" << endl;
                map[(i/3)%colonnesI][(i/3)/lignesI] = 4;
                gm.map.setCase((i/3)%colonnesI,(i/3)/lignesI,4);
                cpt++;
            }

            cout << map[(i/3)%colonnesI][(i/3)/lignesI] << endl ;
        }
        //gm.setMap(goodMap);

        int d = 0;



        for(int i = 0; i < colonnesI; i++){
            for(int j = 0 ; j < lignesI; j++){
               int k =  map[i][j] ;
               int k2 = gm.map.getCase(i,j);
                cout << k << ":" << k2 << " ";
            }
            cout << endl;
        }

    }
    else{
        cout << "Impossible d'ouvrir le fichier" << endl;
    }


}
