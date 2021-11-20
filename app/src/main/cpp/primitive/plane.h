#ifndef MSP_ANDROID_OPENGL_ES_PLANE_H
#define MSP_ANDROID_OPENGL_ES_PLANE_H

#include "vertex.h"

class Plane {
public:
    Plane();
    ~Plane();

    void Draw() const;

private:
    static const unsigned int cNumVertices = 6;
    static const Vertex cBase[cNumVertices];

    GLuint mVao;
    GLuint mVbo;
};

#endif //MSP_ANDROID_OPENGL_ES_PLANE_H
