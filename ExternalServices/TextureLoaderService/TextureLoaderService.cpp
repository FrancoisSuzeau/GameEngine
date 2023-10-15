/******************************************************************************************************************************************/
// File : TextureLoaderService.cpp
// Purpose : Implementing shader loader service
/******************************************************************************************************************************************/
#include "TextureLoaderService.hpp"

namespace Services
{
	void TextureLoaderService::Init()
	{

	}

	void TextureLoaderService::DeInit()
	{
		this->DestroyTexture(texture_id);
	}

	TextureLoaderService::TextureLoaderService()
	{

	}

	TextureLoaderService::~TextureLoaderService()
	{

	}

	unsigned int TextureLoaderService::LoadTexture(std::vector<std::string> faces_path)
	{
		texture_id = 0;
		glGenTextures(1, &texture_id);

		if (texture_id != 0)
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

			if (glIsTexture(texture_id) == GL_TRUE)
			{
				int i = 0;
				for (std::vector<std::string>::iterator it = faces_path.begin(); it != faces_path.end(); it++)
				{
					SDL_Surface* surface = this->LoadFile(it[0]);
					if (surface != nullptr)
					{
						glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
						SDL_FreeSurface(surface);
					}
					i++;
				}

				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			}

			
		}

		return texture_id;
	}

	void TextureLoaderService::DestroyTexture(unsigned int texture_id)
	{
		if (texture_id != 0)
		{
			glDeleteTextures(1, &texture_id);
			texture_id = 0;
		}
	}

	SDL_Surface* TextureLoaderService::LoadFile(std::string path)
	{
		SDL_Surface* surface = IMG_Load(path.c_str());
		if (surface == nullptr)
		{
			SQ_EXTSERVICE_ERROR("Cannot load texture {} | SDL error : {}", path, SDL_GetError());

			return nullptr;
		}

		SQ_EXTSERVICE_TRACE("Texture {} load successfully", path);
		return surface;
	}
}

