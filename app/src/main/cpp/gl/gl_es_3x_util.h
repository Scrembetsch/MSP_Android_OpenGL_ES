#ifndef MSP_ANDROID_OPENGL_ES_GL_ES_3X_UTIL_H
#define MSP_ANDROID_OPENGL_ES_GL_ES_3X_UTIL_H

#include "gl.h"

namespace GlUtil {
    GLuint CreateShader(GLenum shaderType, const char* src);
    GLuint CreateProgram(const char* vtxSrc, const char* fragSrc);
};

#endif //MSP_ANDROID_OPENGL_ES_GL_ES_3X_UTIL_H
