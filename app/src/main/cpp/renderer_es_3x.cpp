#include "gl_es_3x_jni.h"
#include <EGL/egl.h>

#define STR(s) #s
#define STRV(s) STR(s)

#define POS_ATTRIB 0
#define COLOR_ATTRIB 1
#define SCALEROT_ATTRIB 2
#define OFFSET_ATTRIB 3

static const char VERTEX_SHADER[] =
        "#version 300 es\n"
        "layout(location = " STRV(POS_ATTRIB) ") in vec3 pos;\n"
        "layout(location=" STRV(COLOR_ATTRIB) ") in vec4 color;\n"
        "out vec4 vColor;\n"
        "void main() {\n"
        "    gl_Position = vec4(pos, 1.0);\n"
        "    vColor = color;\n"
        "}\n";

static const char FRAGMENT_SHADER[] =
        "#version 300 es\n"
        "precision mediump float;\n"
        "in vec4 vColor;\n"
        "out vec4 outColor;\n"
        "void main() {\n"
        "    outColor = vColor;\n"
        "}\n";

class RendererES3: public Renderer {
public:
    RendererES3();
    virtual ~RendererES3();
    bool init();

private:
    enum {VB_INSTANCE, VB_SCALEROT, VB_OFFSET, VB_COUNT};

    virtual void draw(unsigned int numInstances);

    const EGLContext mEglContext;
    GLuint mProgram;
    GLuint mVbo;
    GLuint mVao;
};

Renderer* createES3Renderer() {
    RendererES3* renderer = new RendererES3;
    if (!renderer->init()) {
        delete renderer;
        return NULL;
    }
    return renderer;
}

RendererES3::RendererES3()
        : mEglContext(eglGetCurrentContext()),
          mProgram(0),
          mVao(0)
{
    mVbo = 0;
}

bool RendererES3::init() {
    mProgram = createProgram(VERTEX_SHADER, FRAGMENT_SHADER);
    if (!mProgram)
        return false;

    glGenVertexArrays(1, &mVao);
    glGenBuffers(1, &mVbo);

    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CUBE), CUBE, GL_STATIC_DRAW);

    glBindVertexArray(mVao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

//    glGenBuffers(VB_COUNT, mVbo);
//    glBindBuffer(GL_ARRAY_BUFFER, mVbo[VB_INSTANCE]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(CUBE), CUBE, GL_STATIC_DRAW);
//    glBindBuffer(GL_ARRAY_BUFFER, mVbo[VB_SCALEROT]);
//    glBufferData(GL_ARRAY_BUFFER, MAX_INSTANCES * 4 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
//    glBindBuffer(GL_ARRAY_BUFFER, mVbo[VB_OFFSET]);
//    glBufferData(GL_ARRAY_BUFFER, MAX_INSTANCES * 2 * sizeof(float), NULL, GL_STATIC_DRAW);
//
//    glGenVertexArrays(1, &mVao);
//    glBindVertexArray(mVao);
//
//    glBindBuffer(GL_ARRAY_BUFFER, mVbo[VB_INSTANCE]);
//    glVertexAttribPointer(POS_ATTRIB, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, pos));
//    glVertexAttribPointer(COLOR_ATTRIB, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, rgba));
//    glEnableVertexAttribArray(POS_ATTRIB);
//    glEnableVertexAttribArray(COLOR_ATTRIB);
//
//    glBindBuffer(GL_ARRAY_BUFFER, mVbo[VB_SCALEROT]);
//    glVertexAttribPointer(SCALEROT_ATTRIB, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
//    glEnableVertexAttribArray(SCALEROT_ATTRIB);
//    glVertexAttribDivisor(SCALEROT_ATTRIB, 1);
//
//    glBindBuffer(GL_ARRAY_BUFFER, mVbo[VB_OFFSET]);
//    glVertexAttribPointer(OFFSET_ATTRIB, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
//    glEnableVertexAttribArray(OFFSET_ATTRIB);
//    glVertexAttribDivisor(OFFSET_ATTRIB, 1);

    ALOGV("Using OpenGL ES 3.0 renderer");
    return true;
}

RendererES3::~RendererES3() {
    /* The destructor may be called after the context has already been
     * destroyed, in which case our objects have already been destroyed.
     *
     * If the context exists, it must be current. This only happens when we're
     * cleaning up after a failed init().
     */
    if (eglGetCurrentContext() != mEglContext)
        return;
    glDeleteVertexArrays(1, &mVao);
    glDeleteBuffers(1, &mVbo);
    glDeleteProgram(mProgram);
}

void RendererES3::draw(unsigned int numInstances) {
    glUseProgram(mProgram);
    glBindVertexArray(mVao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}