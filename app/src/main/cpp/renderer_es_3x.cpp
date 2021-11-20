#include "gl_es_3x_jni.h"
#include <EGL/egl.h>

#include "primitive/cube.h"
#include "primitive/plane.h"
#include "primitive/triangle.h"
#include "gl/gl_es_3x_util.h"
#include "util.h"
#include "glm/glm.hpp"

#define STR(s) #s
#define STRV(s) STR(s)

#define POS_ATTRIB 0
#define COLOR_ATTRIB 1

static const char VERTEX_SHADER[] =
        "#version 300 es\n"
        "layout(location = " STRV(POS_ATTRIB) ") in vec3 aPos;\n"
        "layout(location=" STRV(COLOR_ATTRIB) ") in vec3 aColor;\n"
        "uniform mat4 uProjection;\n"
        "uniform mat4 uView;\n"
        "uniform mat4 uModel;\n"
        "out vec4 vColor;\n"
        "void main() {\n"
        "    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);\n"
        "    vColor = vec4(aColor, 1.0);\n"
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
    mProgram = GlUtil::CreateProgram(VERTEX_SHADER, FRAGMENT_SHADER);
    if (!mProgram)
        return false;

    glEnable(GL_DEPTH_TEST);

    LOGV("RENDERER3x", "Using OpenGL ES 3.0 renderer");
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
    glUniformMatrix4fv(glGetUniformLocation(mProgram, "uProjection"), 1, GL_FALSE, &mProjectionMat[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(mProgram, "uView"), 1, GL_FALSE, &mViewMat[0][0]);
    mMesh.Draw(mProgram);
}