#include "cube.h"

Cube::Cube(GLWidget277 *context) : Drawable(context)
{}

void Cube::create()
{
    // creates a quad in upper right quadrant (0 to 1)
    GLuint idx[6]{0, 1, 2, 0, 2, 3};
    glm::vec4 vert_pos[4] {glm::vec4(0.f, 0.f, 0.f, 1.f),
                           glm::vec4(1.f, 0.f, 0.f, 1.f),
                           glm::vec4(1.f, 0.f, 1.f, 1.f),
                           glm::vec4(0.f, 0.f, 1.f, 1.f)};


    glm::vec4 vert_nor[4] {glm::vec4(0.f, 1.f, 0.f, 0.f),
                           glm::vec4(0.f, 1.f, 0.f, 0.f),
                           glm::vec4(0.f, 1.f, 0.f, 0.f),
                           glm::vec4(0.f, 1.f, 0.f, 0.f)};

    glm::vec4 vert_col[4] {glm::vec4(0.f, 1.f, 0.f, 1.f),
                           glm::vec4(0.f, 1.f, 0.f, 1.f),
                           glm::vec4(0.f, 1.f, 0.f, 1.f),
                           glm::vec4(0.f, 1.f, 0.f, 1.f)};
    count = 6;

    generateIdx();
    mp_context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    mp_context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), idx, GL_STATIC_DRAW);

    generatePos();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    mp_context->glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec4), vert_pos, GL_STATIC_DRAW);

    generateNor();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
    mp_context->glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec4), vert_nor, GL_STATIC_DRAW);

    generateCol();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    mp_context->glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec4), vert_col, GL_STATIC_DRAW);

}
