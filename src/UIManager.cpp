//
// Created by Quentin on 14/12/2016.
//

#include "../include/UIManager.h"


UIManager::UIManager() {
    sphere = new glimac::Sphere(1, 32, 16);

}

void UIManager::initSDL(float largeur, float hauteur, const char *name) {
    this->hauteur = hauteur;
    this->largeur = largeur;
    this->windowManager = new glimac::SDLWindowManager(largeur, hauteur, name);
    SDL_EnableUNICODE(1);
}

int UIManager::initGlew() {
    GLenum glewInitError = glewInit();
    if (GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return 1;
    }
}

void UIManager::loadShaders( glimac::Program &program, char** argv) {
    glimac::FilePath applicationPath(argv[0]);
    program = glimac::loadProgram(applicationPath.dirPath() + "\\..\\..\\shaders\\3D.vs.glsl",
                          applicationPath.dirPath() + "\\..\\..\\shaders\\normals.fs.glsl");

}

void UIManager::initOpenGL(glimac::Program &program) {

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    uMVPMatrixLoc = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    uMVMatrixLoc = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    uNormalMatrixLoc = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

    glEnable(GL_DEPTH_TEST);


    ProjMatrix = glm::perspective<float>(glm::radians(70.f),largeur/hauteur,0.1f,100.f);
    MVMatrix = glm::translate<float>(glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1), glm::vec3(0.f,0.f,-5.f));
    NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


    //sphere.getVertexCount();//nb sommets
    //sphere.getDataPointer(); // tab de sommets

    //glGenBuffers(GLsizei n, Gluint*buffers); créer un buffer (nb vbo à créer, pointer id vbo)

    glGenBuffers(1, &vbo); //vbo affecté directement

    /*Binding VBO ->GL_ARRAYY_BUFFER
    glBindBuffer(GLenum target, GLuint buffer)
                nom de la cible , buffer à binder
    */
    glBindBuffer(GL_ARRAY_BUFFER, vbo);



    /*Remplir VBO
    lBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)

   Paramètres:

   GLenum target: la cible sur laquelle le buffer est bindé (GL_ARRAY_BUFFER dans notre cas)
      GLsizeiptr size: la taille du tableau en octets. C'est le nombre de flottants multiplié par la taille d'un float (sizeof(float)).
      const GLvoid* data: le pointeur vers les données, notre tableau de flottants.
   GLenum usage: un flag indiquant à OpenGL quel usage on va faire du buffer. On utilise GL_STATIC_DRAW pour un buffer dont les données ne changeront jamais.


    */
    glBufferData(GL_ARRAY_BUFFER, sphere->getVertexCount()*sizeof(glimac::ShapeVertex), sphere->getDataPointer(), GL_STATIC_DRAW);

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
    /*glVertexAttribPointer(GLuint index,
            GLint size, GLenum type, GLboolean normalized,
            GLsizei stride, const GLvoid* pointer);

    Paramètres:

    GLuint index: l'index de l'attribut à spécifier
    GLint size: le nombre de composantes de l'attribut. Dans notre cas c'est 2 car chaque position est décrite par deux nombres flottants.
    GLenum type: une constante OpenGL indiquant le type de chaque composante. Dans notre cas on passe GL_FLOAT pour indiquer que chaque composante est un nombre flottant.
    GLboolean normalized: pas besoin de s'occuper de ce paramètre pour le moment, on passe GL_FALSE
    GLsizei stride: indique à OpenGL le nombre d'octets séparant l'attribut pour deux sommets consécutifs. Ca ne veut rien dire ? oui je sais. Imaginez vous être OpenGL. Vous venez de lire une position dans le tableau. Vous avez besoin de savoir ou est situé la position suivante. Dans notre cas elle est juste après, il faut donc avancer de deux flottants, soit 2 * sizeof(GLfloat) octets. Nous verrons dans l'exercice suivant que la position suivante peut être situé plus loin dans le tableau lorsqu'on rajoute des attributs de sommet.
    const GLvoid* pointer: un pointeur, ou pas. Ce paramètre est un piège. Il faut en fait passer l'offset (décalage) en octets de la premiere instance de l'attribut dans le tableau. OK, ça ne veut encore rien dire. Dans notre cas, la première position est située au début du tableau, l'offset est donc 0.
    */

    //on rebind vbo pour lui indiquer lequel il doit utiliser
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex),
                          (const GLvoid *) (offsetof(glimac::ShapeVertex, position)));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex),
                          (const GLvoid *) (offsetof(glimac::ShapeVertex, normal)));
    glVertexAttribPointer(VERTEX_ATTR_TEXCORD, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex),
                          (const GLvoid *) (offsetof(glimac::ShapeVertex, texCoords)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



}

void UIManager::render(GameManager* gm) {

    /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/


    //Nettoyer la fenetre, para indique ce qu'il faut nettoyer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(int i = 0 ; i < gm->map->getColumns() ; i++){
        for(int j = 0 ; j < gm->map->getLines() ; j++){
            gm->map->map3D[i][j].draw(gm->player->camera->getViewMatrix());
        }
    }




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

void UIManager::updateDisplay() {
    windowManager->swapBuffers();
}

void UIManager::freeRessources() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

}


/*
void UIManager::drawCube(Cube cube) {



    glGenBuffers(1, &vbo); //vbo affecté directement
    glBindBuffer(GL_ARRAY_BUFFER, vbo);


    glBufferData(GL_ARRAY_BUFFER, cube.geometry.getVertexCount()*sizeof(glimac::Geometry::Vertex), cube.geometry.getVertexBuffer(), GL_STATIC_DRAW);

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
    /*glVertexAttribPointer(GLuint index,
            GLint size, GLenum type, GLboolean normalized,
            GLsizei stride, const GLvoid* pointer);

    Paramètres:

    GLuint index: l'index de l'attribut à spécifier
    GLint size: le nombre de composantes de l'attribut. Dans notre cas c'est 2 car chaque position est décrite par deux nombres flottants.
    GLenum type: une constante OpenGL indiquant le type de chaque composante. Dans notre cas on passe GL_FLOAT pour indiquer que chaque composante est un nombre flottant.
    GLboolean normalized: pas besoin de s'occuper de ce paramètre pour le moment, on passe GL_FALSE
    GLsizei stride: indique à OpenGL le nombre d'octets séparant l'attribut pour deux sommets consécutifs. Ca ne veut rien dire ? oui je sais. Imaginez vous être OpenGL. Vous venez de lire une position dans le tableau. Vous avez besoin de savoir ou est situé la position suivante. Dans notre cas elle est juste après, il faut donc avancer de deux flottants, soit 2 * sizeof(GLfloat) octets. Nous verrons dans l'exercice suivant que la position suivante peut être situé plus loin dans le tableau lorsqu'on rajoute des attributs de sommet.
    const GLvoid* pointer: un pointeur, ou pas. Ce paramètre est un piège. Il faut en fait passer l'offset (décalage) en octets de la premiere instance de l'attribut dans le tableau. OK, ça ne veut encore rien dire. Dans notre cas, la première position est située au début du tableau, l'offset est donc 0.
    */

   // on rebind vbo pour lui indiquer lequel il doit utiliser
 /*   glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex),
                          (const GLvoid *) (offsetof(glimac::ShapeVertex, position)));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex),
                          (const GLvoid *) (offsetof(glimac::ShapeVertex, normal)));
    glVertexAttribPointer(VERTEX_ATTR_TEXCORD, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex),
                          (const GLvoid *) (offsetof(glimac::ShapeVertex, texCoords)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



}
*/


