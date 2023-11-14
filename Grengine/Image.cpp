#include "pch.h"
#include "Image.h"

Spite::Image::Image(unsigned char* data, glm::ivec2 dimensions) : data{ data, data + (dimensions.x * dimensions.y * 4)}, dimensions{dimensions}
{
}
