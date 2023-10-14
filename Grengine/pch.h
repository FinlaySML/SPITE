#pragma once
#include <memory>
#include <vector>
#include <string>
#include <span>
#include <tuple>
#include <unordered_map>
#include <chrono>
#include <iostream>
#include <fstream>
#include <array>
#include <thread>
#include <algorithm>
#include <ranges>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <stb_image.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
#if defined(_WIN32) || defined(_WIN64)
#define NOMINMAX
#include <Windows.h>
#endif
