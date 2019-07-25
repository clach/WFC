#pragma once

#include "drawable.h"
#include <memory>
#include <texture.h>

class Mesh : public Drawable
{
public:
    Mesh(GLWidget277*);
    void create() override;

    void createFromOBJ(const char *filename, const char* textureFile);
    void createCube();

    void bindTexture() const;
    void loadTexture() const;

    void setInstanceVBOs(std::vector<glm::vec3> trans, std::vector<glm::vec3> rot);

private:
    std::unique_ptr<Texture> mp_texture;
};
