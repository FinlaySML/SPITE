#pragma once
#include "Texture.h"
namespace Spite {
    class Texture_GL : public Texture {
        public:
            ~Texture_GL() final;
            unsigned int GetHandle();
        private:
            unsigned int handle;
            bool GetShouldFlipTextures() final;
            void SendToGPU(stbi_uc* pixelData, int x, int y) final;

    };
}