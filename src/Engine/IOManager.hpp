#pragma once
#include <vector>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL.h>
#include <stb_image.h>

#include "Data.hpp"
#include "Debug.hpp"


namespace Engine
{
    extern GLTexture LoadImageToGLTexture(std::string filePath, GLint sourceFormat, GLint format);
}