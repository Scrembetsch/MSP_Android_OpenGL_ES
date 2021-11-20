#include "plane.h"

const Vertex Plane::cBase[cNumVertices] =
        {
                {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
                {{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
                {{0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
                {{0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
                {{-0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
                {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        };

Plane::Plane()
        : mVao(0)
        , mVbo(0)
{
    glGenVertexArrays(1, &mVao);
    glGenBuffers(1, &mVbo);

    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cBase), cBase, GL_STATIC_DRAW);

    glBindVertexArray(mVao);
    glVertexAttribPointer(Vertex::Attribute::POSITION, Vertex::GetPositionSize(), GL_FLOAT, GL_FALSE, Vertex::GetVertexSize(), Vertex::GetPositionOffset());
    glEnableVertexAttribArray(Vertex::Attribute::POSITION);
    glVertexAttribPointer(Vertex::Attribute::COLOR, Vertex::GetColorSize(), GL_FLOAT, GL_FALSE, Vertex::GetVertexSize(), Vertex::GetColorOffset());
    glEnableVertexAttribArray(Vertex::Attribute::COLOR);
}

Plane::~Plane()
{
    glDeleteBuffers(1, &mVbo);
    glDeleteVertexArrays(1, &mVao);
}

void Plane::Draw() const
{
    glBindVertexArray(mVao);
    glDrawArrays(GL_TRIANGLES, 0, cNumVertices);
}