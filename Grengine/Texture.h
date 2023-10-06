#pragma once
#include "pch.h"
namespace Spite {
	class Texture {
	public:
		Texture(const std::string& file);
		Texture();
		void LoadFromFile(const std::string& file);
		virtual ~Texture();
		bool IsLoaded();
	private:
		bool loaded;
	protected:
		void SetLoaded(bool l);
		virtual bool GetShouldFlipTextures() = 0;
		virtual void SendToGPU(stbi_uc* pixelData, int x, int y) = 0;
	};
}

