#include "pch.h"
#include "Texture_GL.h"

Spite::Texture_GL::~Texture_GL() {
    if(IsLoaded()) {
        glDeleteTextures(1, &handle);
    }
}

unsigned int Spite::Texture_GL::GetHandle() {
    if(!IsLoaded()) {
        std::cout << "You should not use a texture that isn't loaded!" << std::endl;
    }
    return handle;
}

bool Spite::Texture_GL::GetShouldFlipTextures() {
	return true;
}

void Spite::Texture_GL::SendToGPU(stbi_uc* pixelData, int x, int y) {
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}
