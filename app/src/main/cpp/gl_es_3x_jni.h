#ifndef GL_ES_3X_JNI_H
#define GL_ES_3X_JNI_H 1

#include <android/log.h>
#include <math.h>

#include "gl.h"

#define DEBUG 1

#define LOG_TAG "GL_ES_3X_JNI"
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#if DEBUG
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#else
#define ALOGV(...)
#endif

// returns true if a GL error occurred
extern bool checkGlError(const char* funcName);
extern GLuint createShader(GLenum shaderType, const char* src);
extern GLuint createProgram(const char* vtxSrc, const char* fragSrc);

// ----------------------------------------------------------------------------
// Interface to the ES2 and ES3 renderers, used by JNI code.

class Renderer {
public:
    virtual ~Renderer();
    void resize(int w, int h);
    void render();

protected:
    Renderer();

    virtual void draw() = 0;

private:
    void calcSceneParams(unsigned int w, unsigned int h, float* offsets);
    void step();

    uint64_t mLastFrameNs;
};

extern Renderer* createES3Renderer();

#endif // GL_ES_3X_JNI_H