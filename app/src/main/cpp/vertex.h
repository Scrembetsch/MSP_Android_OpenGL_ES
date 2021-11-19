#ifndef MSP_ANDROID_OPENGL_ES_VERTEX_H
#define MSP_ANDROID_OPENGL_ES_VERTEX_H

#include "gl.h"

class Vertex {
public:
    GLfloat Position[3];
    GLfloat Color[3];

    enum Attribute
    {
        POSITION,
        COLOR,

        NUM_ATTRIBUTES
    };

    static GLint GetPositionSize();
    static GLint GetColorSize();
    static GLint GetVertexSize();

    static void* GetPositionOffset();
    static void* GetColorOffset();
};

#endif //MSP_ANDROID_OPENGL_ES_VERTEX_H
