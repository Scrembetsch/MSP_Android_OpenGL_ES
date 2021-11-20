#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <thread>

#include "gl_es_3x_jni.h"
#include "gl/gl_es_3x_util.h"
#include "glm/gtc/matrix_transform.hpp"
#include "util.h"

Renderer::Renderer()
{
}

Renderer::~Renderer() {
}

void Renderer::resize(int w, int h) {
    glViewport(0, 0, w, h);
    mProjectionMat = glm::perspective(glm::radians(45.0f), float(w) / float(h), 0.1f, 100.0f);
    mViewMat = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Renderer::calcSceneParams(unsigned int w, unsigned int h,
                               float* offsets) {
}

void Renderer::step() {
    timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    auto nowNs = now.tv_sec*1000000000ull + now.tv_nsec;

    mMesh.mModel = glm::rotate(mMesh.mModel, glm::radians(1.0f), glm::vec3(0.1f, 0.2f, 0.3f));

    mLastFrameNs = nowNs;
}

void Renderer::render() {
    step();

    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
    GlUtil::CheckGlError("Renderer::render");
}

// ----------------------------------------------------------------------------

static Renderer* g_renderer = NULL;
//static std::thread g_thread;

#if !defined(DYNAMIC_ES3)
static GLboolean gl3stubInit() {
    return GL_TRUE;
}
#endif

extern "C" JNIEXPORT void JNICALL
Java_at_tributsch_msp_1android_1opengl_1es_GlEs30JniLib_init(JNIEnv* env, jclass obj) {
    if (g_renderer) {
        delete g_renderer;
        g_renderer = NULL;
    }

    GlUtil::PrintGlString("Version", GL_VERSION);
    GlUtil::PrintGlString("Vendor", GL_VENDOR);
    GlUtil::PrintGlString("Renderer", GL_RENDERER);
    GlUtil::PrintGlString("Extensions", GL_EXTENSIONS);

    const char* versionStr = (const char*)glGetString(GL_VERSION);
    if (strstr(versionStr, "OpenGL ES 3.") && gl3stubInit()) {
        g_renderer = createES3Renderer();
//        g_thread = std::thread(
//                []()
//                {
//                    while(true)
//                    {
//                        g_renderer->render();
//                    }
//                }
//        );
    } else {
        LOGE("JNI_BRIDGE", "Unsupported OpenGL ES version");
    }
}

extern "C" JNIEXPORT void JNICALL
Java_at_tributsch_msp_1android_1opengl_1es_GlEs30JniLib_resize(JNIEnv* env, jclass obj, jint width, jint height) {
    if (g_renderer) {
        g_renderer->resize(width, height);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_at_tributsch_msp_1android_1opengl_1es_GlEs30JniLib_step(JNIEnv* env, jclass obj) {
    if (g_renderer) {
        g_renderer->render();
    }
}