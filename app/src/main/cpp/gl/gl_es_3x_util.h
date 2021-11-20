#ifndef MSP_ANDROID_OPENGL_ES_GL_ES_3X_UTIL_H
#define MSP_ANDROID_OPENGL_ES_GL_ES_3X_UTIL_H

#include "gl.h"

namespace GlUtil {
    bool CheckGlError(const char* funcName);
    GLuint CreateShader(GLenum shaderType, const char* src);
    GLuint CreateProgram(const char* vtxSrc, const char* fragSrc);
    void PrintGlString(const char* name, GLenum s);
};

#endif //MSP_ANDROID_OPENGL_ES_GL_ES_3X_UTIL_H
