#pragma once
#include "Texture.h"
namespace Spite {
    class Texture_GL : public Texture {
    public:
        Texture_GL();
        ~Texture_GL() final;
        void LoadFromFile(const std::string& file) final;
        void LoadFromData(std::span<unsigned char> data, unsigned x, unsigned y) final;
        void Resize(glm::ivec2 newDimensions) final;
        void Blit(const TextureRegion& source, glm::ivec2 offset) final;
        bool IsLoaded() final;
        glm::ivec2 GetDimensions() final;
        const std::optional<std::string>& Path() final;
        unsigned int GetHandle();
    private:
        bool loaded;
        glm::ivec2 dimensions;
        unsigned int handle;
        std::optional<std::string> path;
    };
}