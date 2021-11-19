#ifndef MSP_ANDROID_OPENGL_ES_PLANE_H
#define MSP_ANDROID_OPENGL_ES_PLANE_H

#include "vertex.h"

class Plane {
private:
    GLuint mVao;
    GLuint mVbo;

public:
    Plane();
    ~Plane();

    void Draw() const;

private:
    static const unsigned int cNumVertices = 6;
    static const Vertex cBase[cNumVertices];
};

#endif //MSP_ANDROID_OPENGL_ES_PLANE_H
