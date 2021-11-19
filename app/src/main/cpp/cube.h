#ifndef MSP_ANDROID_OPENGL_ES_CUBE_H
#define MSP_ANDROID_OPENGL_ES_CUBE_H

#include "vertex.h"

class Cube {
private:
    GLuint mVao;
    GLuint mVbo;

public:
    Cube();
    ~Cube();

    void Draw() const;

private:
    static const unsigned int cNumVertices = 36;
    static const Vertex cBaseCube[cNumVertices];
};

#endif //MSP_ANDROID_OPENGL_ES_CUBE_H
