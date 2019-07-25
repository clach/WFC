#include "instancedmesh.h"
#include <tinyobj/tiny_obj_loader.h>
#include <iostream>
#include <QFile>

InstancedMesh::InstancedMesh(GLWidget277 *context)
    : Drawable(context), mp_texture(nullptr)
{}

void InstancedMesh::createCube()
{
    // will need 24 positions to match with 24 normals
    std::vector<glm::vec4> pos {glm::vec4(1, -1, 1, 1), glm::vec4(1, 1, 1, 1), // front quad
                                glm::vec4(-1, 1, 1, 1), glm::vec4(-1, -1, 1, 1),

                                glm::vec4(-1, -1, -1, 1), glm::vec4(-1, 1, -1, 1), // back quad
                                glm::vec4(1, 1, -1, 1), glm::vec4(1, -1, -1, 1),

                                glm::vec4(1, -1, -1, 1), glm::vec4(1, 1, -1, 1), // right quad
                                glm::vec4(1, 1, 1, 1), glm::vec4(1, -1, 1, 1),

                                glm::vec4(-1, -1, 1, 1), glm::vec4(-1, 1, 1, 1), // left quad
                                glm::vec4(-1, 1, -1, 1), glm::vec4(-1, -1, -1, 1),

                                glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, -1, 1), // top quad
                                glm::vec4(-1, 1, -1, 1), glm::vec4(-1, 1, 1, 1),

                                glm::vec4(1, -1, -1, 1), glm::vec4(1, -1, 1, 1), // bottom quad
                                glm::vec4(-1, -1, 1, 1), glm::vec4(-1, -1, -1, 1) };

    // each quad of the cube has the same normals
    // each vertex touches 3 faces -> 8 vertices * 3 faces = 24 normals
    // or, 4 normals for each of the 6 faces
    std::vector<glm::vec4> nor {glm::vec4(0, 0, 1, 0), glm::vec4(0, 0, 1, 0), // front quad
                                glm::vec4(0, 0, 1, 0), glm::vec4(0, 0, 1, 0),

                                glm::vec4(0, 0, -1, 0), glm::vec4(0, 0, -1, 0), // back quad
                                glm::vec4(0, 0, -1, 0), glm::vec4(0, 0, -1, 0),

                                glm::vec4(1, 0, 0, 0), glm::vec4(1, 0, 0, 0), // right quad
                                glm::vec4(1, 0, 0, 0), glm::vec4(1, 0, 0, 0),

                                glm::vec4(-1, 0, 0, 0), glm::vec4(-1, 0, 0, 0), // left quad
                                glm::vec4(-1, 0, 0, 0), glm::vec4(-1, 0, 0, 0),

                                glm::vec4(0, 1, 0, 0), glm::vec4(0, 1, 0, 0), // top quad
                                 glm::vec4(0, 1, 0, 0), glm::vec4(0, 1, 0, 0),

                                glm::vec4(0, -1, 0, 0), glm::vec4(0, -1, 0, 0), // bottom quad
                                glm::vec4(0, -1, 0, 0), glm::vec4(0, -1, 0, 0) };

    // each face can have the same UVs
    std::vector<glm::vec2> uvs {glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1), // front quad
                                glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1), // back quad
                                glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1), // right quad
                                glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1), // left quad
                                glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1), // top quad
                                glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1)};  // bottom quad

    std::vector<glm::vec4> col;
    for (int i = 0; i < 24; i++) {
        col.push_back(glm::vec4(1, 1, 1, 0.5));
    }

    // cube has 6 sides, will have 12 triangles, 12 * 3 indices
    std::vector<GLuint> idx {0, 1, 2,
                             0, 2, 3,
                             4, 5, 6,
                             4, 6, 7,
                             8, 9, 10,
                             8, 10, 11,
                             12, 13, 14,
                             12, 14, 15,
                             16, 17, 18,
                             16, 18, 19,
                             20, 21, 22,
                             20, 22, 23};

    count = idx.size();

    generateIdx();
    mp_context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    mp_context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);

    generatePos();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    mp_context->glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(glm::vec4), pos.data(), GL_STATIC_DRAW);

    generateNor();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
    mp_context->glBufferData(GL_ARRAY_BUFFER, nor.size() * sizeof(glm::vec4), nor.data(), GL_STATIC_DRAW);

    generateUV();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufUV);
    mp_context->glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), uvs.data(), GL_STATIC_DRAW);

    //generateCol();
    //mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    //mp_context->glBufferData(GL_ARRAY_BUFFER, col.size() * sizeof(glm::vec4), col.data(), GL_STATIC_DRAW);
}

void InstancedMesh::create()
{
}

void InstancedMesh::bindTexture() const
{
    mp_texture->bind(0);
}

void InstancedMesh::loadTexture() const
{
    mp_texture->load(0);
}

void InstancedMesh::createFromOBJ(const char* filename, const char *textureFile)
{
    std::vector<tinyobj::shape_t> shapes; std::vector<tinyobj::material_t> materials;
    std::string errors = tinyobj::QLoadObj(shapes, materials, filename);
    std::cout << errors << std::endl;
    if(errors.size() == 0)
    {
        count = 0;
        //Read the information from the vector of shape_ts
        for(unsigned int i = 0; i < shapes.size(); i++)
        {
            std::vector<float> &positions = shapes[i].mesh.positions;
            std::vector<float> &normals = shapes[i].mesh.normals;
            std::vector<float> &uvs = shapes[i].mesh.texcoords;
            std::vector<unsigned int> &indices = shapes[i].mesh.indices;

            bool normalsExist = normals.size() > 0;
            bool uvsExist = uvs.size() > 0;


            std::vector<GLuint> glIndices;
            for(unsigned int ui : indices)
            {
                glIndices.push_back(ui);
            }
            std::vector<glm::vec4> glPos;
            std::vector<glm::vec4> glNor;
            std::vector<glm::vec2> glUV;

            for(int x = 0; x < positions.size(); x += 3)
            {
                glPos.push_back(glm::vec4(positions[x], positions[x + 1], positions[x + 2], 1.f));
                if(normalsExist)
                {
                    glNor.push_back(glm::vec4(normals[x], normals[x + 1], normals[x + 2], 1.f));
                }
            }

            if(uvsExist)
            {
                for(int x = 0; x < uvs.size(); x += 2)
                {
                    glUV.push_back(glm::vec2(uvs[x], uvs[x + 1]));
                }
            }

            generateIdx();
            mp_context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
            mp_context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, glIndices.size() * sizeof(GLuint), glIndices.data(), GL_STATIC_DRAW);

            generatePos();
            mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
            mp_context->glBufferData(GL_ARRAY_BUFFER, glPos.size() * sizeof(glm::vec4), glPos.data(), GL_STATIC_DRAW);

            if(normalsExist)
            {
                generateNor();
                mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
                mp_context->glBufferData(GL_ARRAY_BUFFER, glNor.size() * sizeof(glm::vec4), glNor.data(), GL_STATIC_DRAW);
            }

            if(uvsExist)
            {
                generateUV();
                mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufUV);
                mp_context->glBufferData(GL_ARRAY_BUFFER, glUV.size() * sizeof(glm::vec2), glUV.data(), GL_STATIC_DRAW);
            }

            count += indices.size();
        }
    }
    else
    {
        //An error loading the OBJ occurred!
        std::cout << errors << std::endl;
    }

    mp_texture = std::unique_ptr<Texture>(new Texture(mp_context));
    mp_texture->create(textureFile);

}
