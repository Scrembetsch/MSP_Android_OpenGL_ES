#ifndef GL_ES_3X_JNI_H
#define GL_ES_3X_JNI_H 1

#include <math.h>

#include "gl/gl.h"
#include "glm/glm.hpp"
#include "primitive/cube.h"


// ----------------------------------------------------------------------------
// Interface to the ES2 and ES3 renderers, used by JNI code.

class Renderer {
public:
    virtual ~Renderer();
    void resize(int w, int h);
    void render();

protected:
    Renderer();
    glm::mat4 mProjectionMat;
    glm::mat4 mViewMat;
    virtual void draw() = 0;

    Cube mMesh;

private:
    void calcSceneParams(unsigned int w, unsigned int h, float* offsets);
    void step();

    uint64_t mLastFrameNs;

};

extern Renderer* createES3Renderer();

#endif // GL_ES_3X_JNI_H