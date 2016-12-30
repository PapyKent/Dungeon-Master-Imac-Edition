//
// Created by Quentin on 30/12/2016.
//

#include "../include/Model3d.h"

Model3d::Model3d() {

}



Model3d::~Model3d(){
    freeRessources();
}

void Model3d::initModel() {

    initProgram("cube");
    initGlew();
    initGeometry();

    uMVPMatrixLoc = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    uMVMatrixLoc = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    uNormalMatrixLoc = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    uTexture = glGetUniformLocation(program.getGLId(), "uTexture");
    glEnable(GL_DEPTH_TEST);



    int largeur = 800;
    int hauteur = 800;
    ProjMatrix = glm::perspective<float>(glm::radians(70.f),largeur/hauteur,0.1f,100.f);
    MVMatrix = glm::translate<float>(glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1), glm::vec3(0.f,0.f,0.f));
    NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


    //texture
    this->texture = glimac::loadImage("../../assets/textures/"+text+".jpg");
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D,textureID);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,this->texture->getWidth(),this->texture->getHeight(),0,GL_RGBA,GL_FLOAT ,this->texture->getPixels());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D,0);

    glGenBuffers(1, &vbo); //vbo affecté directement

    //Binding VBO ->GL_ARRAYY_BUFFER

    glBindBuffer(GL_ARRAY_BUFFER, vbo);


    //Remplir VBO

    glBufferData(GL_ARRAY_BUFFER, this->geometry.getVertexCount()*sizeof(glimac::Geometry::Vertex), this->geometry.getVertexBuffer(), GL_STATIC_DRAW);

    //Debinder glBindBufer avec second para 0
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glGenVertexArrays(1, &vao);


    //binding du vao : pas de cible car une seule cible possible pour vao
    glBindVertexArray(vao);

    //activation des attributs de vertex, prend en para l'index renseignant le type de data
    //on prefere les déclarer auparavant dans des constantes plutot que en clair

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCORD);


    //spécification des attributs de vertex

    //on rebind vbo pour lui indiquer lequel il doit utiliser
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::Geometry::Vertex),
                          (const GLvoid *) (offsetof(glimac::Geometry::Vertex, m_Position)));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::Geometry::Vertex),
                          (const GLvoid *) (offsetof(glimac::Geometry::Vertex, m_Normal)));
    glVertexAttribPointer(VERTEX_ATTR_TEXCORD, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Geometry::Vertex),
                          (const GLvoid *) (offsetof(glimac::Geometry::Vertex, m_TexCoords)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


}

void Model3d::initProgram(std::string path) {
    program = glimac::loadProgram("../../shaders/3D.vs.glsl",
                                  "../../shaders/tex3D.fs.glsl");
    program.use();
}

void Model3d::initGeometry() {
    geometry.loadOBJ("../../assets/models/"+model+".obj", "../../assets/models/"+model+".mtl");
}

void Model3d::draw(glm::mat4 viewMatrix) {
    /*********************************
        * HERE SHOULD COME THE RENDERING CODE
        *********************************/

    //modifs
    this->MVMatrix = glm::translate(glm::mat4(1), this->position); // Translation
    this->NormalMatrix = glm::transpose(glm::inverse(this->MVMatrix));

    //envoyer les matrices
    glUniformMatrix4fv(uMVPMatrixLoc,1,GL_FALSE,glm::value_ptr(ProjMatrix *  viewMatrix * MVMatrix ));
    glUniformMatrix4fv(uMVMatrixLoc,1,GL_FALSE,glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uNormalMatrixLoc,1,GL_FALSE,glm::value_ptr(NormalMatrix));

    glBindTexture(GL_TEXTURE_2D,textureID);
    glUniform1i(uTexture,0);

    //Dessiner avec le VAO
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, geometry.getVertexCount());
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D,0);




/*
    for(int i =0;i<32;i++){
        glm::mat4 MVMatrix2 = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5)); // Translation
        MVMatrix2 = glm::rotate(MVMatrix2, windowManager->getTime()/i, glm::vec3(1,1,1)); // Translation * Rotation
        MVMatrix2 = glm::translate(MVMatrix2, glm::vec3(-2, 0, 0)); // Translation * Rotation * Translation
        MVMatrix2 = glm::scale(MVMatrix2, glm::vec3(0.2, 0.2, 0.2)); // Translation * Rotation * Translation * Scale

        glm::mat4 NormalMatrix2;
        NormalMatrix2 = glm::transpose(glm::inverse(MVMatrix2));


        glUniformMatrix4fv(uMVPMatrixLoc,1,GL_FALSE,glm::value_ptr(ProjMatrix * MVMatrix2));
        glUniformMatrix4fv(uMVMatrixLoc,1,GL_FALSE,glm::value_ptr(MVMatrix2));
        glUniformMatrix4fv(uNormalMatrixLoc,1,GL_FALSE,glm::value_ptr(NormalMatrix2));
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, sphere->getVertexCount());
        glBindVertexArray(0);
    }*/
}

int Model3d::initGlew() {
    GLenum glewInitError = glewInit();
    if (GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return 1;
    }
}

void Model3d::freeRessources() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteTextures(1,&textureID);

}


