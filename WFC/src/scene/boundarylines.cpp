#include "boundarylines.h"

BoundaryLines::BoundaryLines(GLWidget277 *context) : Drawable(context)
{}

void BoundaryLines::create() {
    // set up VBOs to draw boundary lines

    glm::vec4 color = glm::vec4(1.f);
    glm::vec4 normal = glm::vec4(0.f, 0.f, 0.f, 0.f);

    std::vector<GLuint> indices;
    std::vector<glm::vec4> vertexNor;
    std::vector<glm::vec4> vertexCol;

    // TODO: um fix this nasty code
    int vertexCount = 8;

    glm::vec4 vertexPos[8] {glm::vec4(0.f, 0.f, 0.f, 1.f),
                           glm::vec4(1.f, 0.f, 0.f, 1.f),
                           glm::vec4(1.f, 0.f, 1.f, 1.f),
                           glm::vec4(0.f, 0.f, 1.f, 1.f),

                           glm::vec4(0.f, 1.f, 0.f, 1.f),
                           glm::vec4(1.f, 1.f, 0.f, 1.f),
                           glm::vec4(1.f, 1.f, 1.f, 1.f),
                           glm::vec4(0.f, 1.f, 1.f, 1.f)};


    for (int i = 0; i < vertexCount; i++) {
        vertexNor.push_back(normal);
        vertexCol.push_back(color);
    }

    indices.push_back(0);
    for (int i = 0; i < 3; i++) {
        indices.push_back(i + 1);
        indices.push_back(i + 1);
    }
    indices.push_back(0);

    indices.push_back(4);
    for (int i = 0; i < 3; i++) {
        indices.push_back(i + 5);
        indices.push_back(i + 5);
    }
    indices.push_back(4);

    for (int i = 0; i < 4; i++) {
        indices.push_back(i + 4);
        indices.push_back(i);
    }

    count = indices.size();

    generateIdx();
    mp_context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    mp_context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    generatePos();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    mp_context->glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(glm::vec4), vertexPos, GL_STATIC_DRAW);

    generateNor();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
    mp_context->glBufferData(GL_ARRAY_BUFFER, vertexNor.size() * sizeof(glm::vec4), vertexNor.data(), GL_STATIC_DRAW);

    generateCol();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    mp_context->glBufferData(GL_ARRAY_BUFFER, vertexCol.size() * sizeof(glm::vec4), vertexCol.data(), GL_STATIC_DRAW);

}

GLenum BoundaryLines::drawMode() {
    return GL_LINES;
}
