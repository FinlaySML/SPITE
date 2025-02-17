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
#include <typeinfo>
#include <type_traits>
#include <stdexcept>
#include <functional>
#include <filesystem>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <yaml-cpp/yaml.h>
#include <stb_image.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#if defined(_WIN32) || defined(_WIN64)
#define NOMINMAX
#include <Windows.h>
#endif
