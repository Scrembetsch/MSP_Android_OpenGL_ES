#include "gl_es_3x_jni.h"
#include <EGL/egl.h>

#include "cube.h"
#include "plane.h"
#include "triangle.h"

#define STR(s) #s
#define STRV(s) STR(s)

#define POS_ATTRIB 0
#define COLOR_ATTRIB 1

static const char VERTEX_SHADER[] =
        "#version 300 es\n"
        "layout(location = " STRV(POS_ATTRIB) ") in vec3 pos;\n"
        "layout(location=" STRV(COLOR_ATTRIB) ") in vec3 color;\n"
        "out vec4 vColor;\n"
        "void main() {\n"
        "    gl_Position = vec4(pos, 1.0);\n"
        "    vColor = vec4(color, 1.0);\n"
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
    virtual void draw();

    const EGLContext mEglContext;
    GLuint mProgram;
    Cube mMesh;
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
        : mEglContext(eglGetCurrentContext())
        , mProgram(0)
{
}

bool RendererES3::init() {
    mProgram = createProgram(VERTEX_SHADER, FRAGMENT_SHADER);
    if (!mProgram)
        return false;

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
    glDeleteProgram(mProgram);
}

void RendererES3::draw() {
    glUseProgram(mProgram);
    mMesh.Draw();
}