#include "../include/Model3d.h"


Model3d::Model3d() {

}


Model3d::~Model3d() {
    freeRessources();
}

void Model3d::initModel(std::string type, Model3dtext *modelTextList) {

    initProgram(type);
    initGlew();
    initGeometry();

    uMVPMatrixLoc = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    uMVMatrixLoc = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    uNormalMatrixLoc = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    uTexture = glGetUniformLocation(program.getGLId(), "uTexture");

    uKd = glGetUniformLocation(program.getGLId(), "uKd");
    uKs = glGetUniformLocation(program.getGLId(), "uKs");
    uShininess = glGetUniformLocation(program.getGLId(), "uShininess");

    uLightPos_vs = glGetUniformLocation(program.getGLId(), "uLightPos_vs");
    uLightIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");

    glEnable(GL_DEPTH_TEST);


    int largeur = 800;
    int hauteur = 800;


    ProjMatrix = glm::perspective<float>(glm::radians(70.f), largeur / hauteur, 0.1f, 100.f);
    MVMatrix = glm::translate<float>(glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1),
                                     glm::vec3(0.f, 0.f, 0.f));
    NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    //texture
/*     model3Dtext *tmpText = modelTextList->textureExist(text);
     if (tmpText == NULL) {
         modelTextList->addModel3dtexture(text);
         tmpText = modelTextList->textureExist(text);
     }

     this->texture.reset(tmpText->texture);
     textureID = tmpText->textureID;*/


    this->texture = glimac::loadImage("../../assets/textures/" + text + ".png");
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->texture->getWidth(), this->texture->getHeight(), 0, GL_RGBA, GL_FLOAT,
                 this->texture->getPixels());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    glGenBuffers(1, &vbo); //vbo affecté directement

    //Binding VBO ->GL_ARRAYY_BUFFER

    glBindBuffer(GL_ARRAY_BUFFER, vbo);


    //Remplir VBO

    glBufferData(GL_ARRAY_BUFFER, this->geometry.getVertexCount() * sizeof(glimac::Geometry::Vertex),
                 this->geometry.getVertexBuffer(), GL_STATIC_DRAW);

    //Debinder glBindBufer avec second para 0
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // => Creation du IBO

    glGenBuffers(1, &ibo);

    // => On bind sur GL_ELEMENT_ARRAY_BUFFER, cible reservée pour les IBOs
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // => Tableau d'indices: ce sont les indices des sommets à dessiner



    // => On remplit l'IBO avec les indices:
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->geometry.getIndexCount() * sizeof(uint32_t),
                 this->geometry.getIndexBuffer(), GL_STATIC_DRAW);

    // => Comme d'habitude on debind avant de passer à autre chose
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    glGenVertexArrays(1, &vao);


    //binding du vao : pas de cible car une seule cible possible pour vao
    glBindVertexArray(vao);
    // => On bind l'IBO sur GL_ELEMENT_ARRAY_BUFFER; puisqu'un VAO est actuellement bindé,
    // cela a pour effet d'enregistrer l'IBO dans le VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

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
    geometry.loadOBJ("../../assets/models/" + model + ".obj", "../../assets/models/" + model + ".mtl");
}

void Model3d::draw(glm::mat4 viewMatrix, glm::vec3 posPlayer) {
    /*********************************
        * HERE SHOULD COME THE RENDERING CODE
        *********************************/

    //modifs
    this->MVMatrix = glm::translate(glm::mat4(1), this->position); // Translation
    this->NormalMatrix = glm::transpose(glm::inverse(this->MVMatrix));

    //envoyer les matrices
    glUniformMatrix4fv(uMVPMatrixLoc, 1, GL_FALSE, glm::value_ptr(ProjMatrix * viewMatrix * MVMatrix));
    glUniformMatrix4fv(uMVMatrixLoc, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uNormalMatrixLoc, 1, GL_FALSE, glm::value_ptr(NormalMatrix));



    //glUniform3f(uKd,this->geometry.material.m_Kd.x,this->geometry.material.m_Kd.y,this->geometry.material.m_Kd.z);//coeff reflec obj
    //glUniform3f(uKs,this->geometry.material.m_Ks.x,this->geometry.material.m_Ks.y,this->geometry.material.m_Ks.z);//coeff reflec glossi
    //glUniform1f(uShininess,this->geometry.material.m_Shininess);//exposant de brillance

    glUniform3f(uKd, 0.5, 0.5, 0.5);//coeff reflec obj
    glUniform3f(uKs, 0.5, 0.5, 0.5);//coeff reflec glossi
    glUniform1f(uShininess, 0.1);//exposant de brillance


    glUniform3f(uLightPos_vs, posPlayer.x, posPlayer.y + 2, posPlayer.z);
    glUniform3f(uLightIntensity, 3.5, 3.5, 3.6);


    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(uTexture, 0);

    //Dessiner avec le VAO
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, this->geometry.getIndexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);


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
    glDeleteTextures(1, &textureID);

}


