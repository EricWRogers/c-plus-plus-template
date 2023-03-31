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

}