#pragma once
#include "Subsystem.h"
#include "Image.h"
namespace Spite {
	class ResourceSystem : public Subsystem
	{
		std::unordered_map<std::string, std::unique_ptr<Image>> images;
	public:
		int Initialise() override;
		int Shutdown() override;
		Image* GetImage(const std::filesystem::path& path);
	};
	extern ResourceSystem* resource;
}

