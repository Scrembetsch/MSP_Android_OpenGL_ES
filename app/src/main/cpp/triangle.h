#ifndef MSP_ANDROID_OPENGL_ES_TRIANGLE_H
#define MSP_ANDROID_OPENGL_ES_TRIANGLE_H

#include "vertex.h"

class Triangle {
private:
    GLuint mVao;
    GLuint mVbo;

public:
    Triangle();
    ~Triangle();

    void Draw() const;

private:
    static const unsigned int cNumVertices = 3;
    static const Vertex cBase[cNumVertices];
};

#endif //MSP_ANDROID_OPENGL_ES_TRIANGLE_H
