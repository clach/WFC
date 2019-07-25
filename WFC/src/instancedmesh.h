#pragma once

#include "drawable.h"
#include <memory>
#include <texture.h>

class InstancedMesh : public Drawable
{
public:
    InstancedMesh(GLWidget277*);
    void create() override;

    void createFromOBJ(const char *filename, const char* textureFile);
    void createFromOBJ(const char *filename, const char* textureFile, const char* bgTextureFile);
    void createCube();

    void bindTexture() const;
    void loadTexture() const;
    void bindBGTexture() const;
    void loadBGTexture() const;

private:
    std::unique_ptr<Texture> mp_texture;
    std::unique_ptr<Texture> mp_bgTexture;
};
