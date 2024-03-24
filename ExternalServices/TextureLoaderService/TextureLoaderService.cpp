/******************************************************************************************************************************************/
// File : TextureLoaderService.cpp
// Purpose : Implementing shader loader service
/******************************************************************************************************************************************/
#include "TextureLoaderService.hpp"

namespace Services
{
	void TextureLoaderService::Init()
	{
		m_skybox_files_name.push_back("right.jpg");
		m_skybox_files_name.push_back("left.jpg");
		m_skybox_files_name.push_back("top.jpg");
		m_skybox_files_name.push_back("bottom.jpg");
		m_skybox_files_name.push_back("front.jpg");
		m_skybox_files_name.push_back("back.jpg");
	}

	void TextureLoaderService::DeInit()
	{
		
	}

	TextureLoaderService::TextureLoaderService()
	{
		m_skybox_files_name.reserve(6);
	}

	TextureLoaderService::~TextureLoaderService()
	{

	}

	unsigned int TextureLoaderService::BuildSkyboxTexture(std::string const repository_path)
	{
		unsigned int texture_id = 0;
		glGenTextures(1, &texture_id);

		if (texture_id != 0)
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

			if (glIsTexture(texture_id) == GL_TRUE)
			{
				int i = 0;
				for (std::vector<std::string>::iterator it = m_skybox_files_name.begin(); it != m_skybox_files_name.end(); it++)
				{
					std::string const full_path = repository_path + "/" + it[0];
					SDL_Surface* surface = this->LoadTexture(full_path);
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

	SDL_Surface* TextureLoaderService::LoadTexture(std::string path)
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

