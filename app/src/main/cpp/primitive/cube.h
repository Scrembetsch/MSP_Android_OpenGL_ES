#ifndef MSP_ANDROID_OPENGL_ES_CUBE_H
#define MSP_ANDROID_OPENGL_ES_CUBE_H

#include "vertex.h"

class Cube {
public:
    Cube();
    ~Cube();

    void Draw(GLuint shader) const;

    glm::mat4 mModel;

private:
    GLuint mVao;
    GLuint mVbo;

    static const unsigned int cNumVertices = 36;
    static const Vertex cBaseCube[cNumVertices];
};

#endif //MSP_ANDROID_OPENGL_ES_CUBE_H
