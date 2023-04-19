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

    extern bool LoadOBJ(std::string path,
		std::vector < glm::vec3 > & out_vertices,
		std::vector < glm::vec2 > & out_uvs,
		std::vector < glm::vec3 > & out_normals
	);
}