#include "boundarylines.h"

BoundaryLines::BoundaryLines(GLWidget277 *context) : Drawable(context)
{}

void BoundaryLines::create() {
    // set up VBOs to draw boundary lines

    glm::vec4 color = glm::vec4(1.f);
    glm::vec4 normal = glm::vec4(0.f, 0.f, 0.f, 0.f);

    std::vector<GLuint> indices;
    std::vector<glm::vec4> vertexPositions;
    std::vector<glm::vec4> vertexNormals;
    std::vector<glm::vec4> vertexColors;

    // TODO: um fix this nasty code
    int vertexCount = 8;

    vertexPositions.push_back(glm::vec4(0.f, 0.f, 0.f, 1.f));
    vertexPositions.push_back(glm::vec4(1.f, 0.f, 0.f, 1.f));
    vertexPositions.push_back(glm::vec4(1.f, 0.f, 1.f, 1.f));
    vertexPositions.push_back(glm::vec4(0.f, 0.f, 1.f, 1.f));

    vertexPositions.push_back(glm::vec4(0.f, 1.f, 0.f, 1.f));
    vertexPositions.push_back(glm::vec4(1.f, 1.f, 0.f, 1.f));
    vertexPositions.push_back(glm::vec4(1.f, 1.f, 1.f, 1.f));
    vertexPositions.push_back(glm::vec4(0.f, 1.f, 1.f, 1.f));

    for (int i = 0; i < vertexCount; i++) {
        vertexNormals.push_back(normal);
        vertexColors.push_back(color);
    }

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
    mp_context->glBufferData(GL_ARRAY_BUFFER, vertexPositions.size() * sizeof(glm::vec4), vertexPositions.data(), GL_STATIC_DRAW);

    generateNor();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
    mp_context->glBufferData(GL_ARRAY_BUFFER, vertexNormals.size() * sizeof(glm::vec4), vertexNormals.data(), GL_STATIC_DRAW);

    generateCol();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    mp_context->glBufferData(GL_ARRAY_BUFFER, vertexColors.size() * sizeof(glm::vec4), vertexColors.data(), GL_STATIC_DRAW);

}

GLenum BoundaryLines::drawMode() {
    return GL_LINES;
}
