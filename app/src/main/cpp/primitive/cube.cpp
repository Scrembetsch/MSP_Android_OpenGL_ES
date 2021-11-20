#include "cube.h"

const Vertex Cube::cBaseCube[cNumVertices] =
    {
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},

        {{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},

        {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}},

        {{0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}},
        {{0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}},
        {{0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}},
        {{0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}},

        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}},
        {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}},
        {{0.5f, -0.5f, 0.5f }, {1.0f, 0.0f, 1.0f}},
        {{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}},

        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}},
        {{0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}},
        {{0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 1.0f}},
        {{0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}},
    };

Cube::Cube()
: mModel(1.0f)
, mVao(0)
, mVbo(0)
{
    glGenVertexArrays(1, &mVao);
    glGenBuffers(1, &mVbo);

    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cBaseCube), cBaseCube, GL_STATIC_DRAW);

    glBindVertexArray(mVao);
    glVertexAttribPointer(Vertex::Attribute::POSITION, Vertex::GetPositionSize(), GL_FLOAT, GL_FALSE, Vertex::GetVertexSize(), Vertex::GetPositionOffset());
    glEnableVertexAttribArray(Vertex::Attribute::POSITION);
    glVertexAttribPointer(Vertex::Attribute::COLOR, Vertex::GetColorSize(), GL_FLOAT, GL_FALSE, Vertex::GetVertexSize(), Vertex::GetColorOffset());
    glEnableVertexAttribArray(Vertex::Attribute::COLOR);
}

Cube::~Cube()
{
    glDeleteBuffers(1, &mVbo);
    glDeleteVertexArrays(1, &mVao);
}

void Cube::Draw(GLuint shader) const
{
    glUniformMatrix4fv(glGetUniformLocation(shader, "uModel"), 1, GL_FALSE, &mModel[0][0]);
    glBindVertexArray(mVao);
    glDrawArrays(GL_TRIANGLES, 0, cNumVertices);
}