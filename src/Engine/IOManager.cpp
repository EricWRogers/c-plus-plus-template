#include "IOManager.hpp"

namespace Engine
{
    GLTexture LoadImageToGLTexture(std::string filePath, GLint sourceFormat, GLint format)
	{
		GLTexture texture;
		int nrChannels;

		glGenTextures(1, &texture.id);
		glBindTexture(GL_TEXTURE_2D, texture.id);

		stbi_set_flip_vertically_on_load(true);
		SDL_RWops *file = SDL_RWFromFile(filePath.c_str(), "rb");

		if (file != NULL)
		{
			int imageDataLength{static_cast<int>(SDL_RWsize(file))};
			void *imageData{SDL_LoadFile_RW(file, nullptr, 1)};

			// convert to stbi thing
			stbi_uc *data = stbi_load_from_memory(static_cast<stbi_uc *>(imageData), imageDataLength, &texture.width, &texture.height, &nrChannels, 4);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, sourceFormat, texture.width, texture.height, 0, format, GL_UNSIGNED_BYTE, data);
			}
			else
			{
				std::cout << "Failed to load texture " << filePath << std::endl;
			}
			stbi_image_free(data);
			// SDL_RWclose(file);
			// SDL_free(imageData);
		}
		else
		{
			Engine::Error("Failed to open file at path : " + filePath);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Problem for future ERIC
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);//GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_set_flip_vertically_on_load(true);

		return texture;
	}

	bool LoadOBJ(
		std::string path,
		std::vector<glm::vec3> &out_vertices,
		std::vector<glm::vec2> &out_uvs,
		std::vector<glm::vec3> &out_normals)
	{
		Engine::Log("Loading OBJ file " + path);

		std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
		std::vector<glm::vec3> temp_vertices;
		std::vector<glm::vec2> temp_uvs;
		std::vector<glm::vec3> temp_normals;

		FILE *file = fopen(path.c_str(), "r");
		if (file == NULL)
		{
			printf("Impossible to open the file ! Are you in the right path?\n");
			getchar();
			return false;
		}

		while (1)
		{

			char lineHeader[128];
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break; // EOF = End Of File. Quit the loop.

			// else : parse lineHeader

			int warningHolder = 0;

			if (strcmp(lineHeader, "v") == 0)
			{
				glm::vec3 vertex;
				warningHolder = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0)
			{
				glm::vec2 uv;
				warningHolder = fscanf(file, "%f %f\n", &uv.x, &uv.y);
				uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
				temp_uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0)
			{
				glm::vec3 normal;
				warningHolder = fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0)
			{
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9)
				{
					printf("File can't be read by our simple parser :-( Try exporting with other options\n");
					fclose(file);
					return false;
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
			else
			{
				// Probably a comment, eat up the rest of the line
				char stupidBuffer[1000];
				char *realStupidBuffer;
				realStupidBuffer = fgets(stupidBuffer, 1000, file);
			}
		}

		// For each vertex of each triangle
		for (unsigned int i = 0; i < vertexIndices.size(); i++)
		{

			// Get the indices of its attributes
			unsigned int vertexIndex = vertexIndices[i];
			unsigned int uvIndex = uvIndices[i];
			unsigned int normalIndex = normalIndices[i];

			// Get the attributes thanks to the index
			glm::vec3 vertex = temp_vertices[vertexIndex - 1];
			glm::vec2 uv = temp_uvs[uvIndex - 1];
			glm::vec3 normal = temp_normals[normalIndex - 1];

			// Put the attributes in buffers
			out_vertices.push_back(vertex);
			out_uvs.push_back(uv);
			out_normals.push_back(normal);
		}
		fclose(file);
		return true;
	}
}