#pragma once

namespace Spite {
    class Image
    {
        std::vector<unsigned char> data;
        glm::ivec2 dimensions;
    public:
        Image(unsigned char* data, glm::ivec2 dimensions);
    };
}