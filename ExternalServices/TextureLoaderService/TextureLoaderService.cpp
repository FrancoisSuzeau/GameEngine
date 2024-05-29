/******************************************************************************************************************************************/
// File : TextureLoaderService.cpp
// Purpose : Implementing shader loader service
/******************************************************************************************************************************************/
#include "TextureLoaderService.hpp"

namespace Services
{
	void TextureLoaderService::Init()
	{
		m_skybox_files_name.push_back("right");
		m_skybox_files_name.push_back("left");
		m_skybox_files_name.push_back("top");
		m_skybox_files_name.push_back("bottom");
		m_skybox_files_name.push_back("front");
		m_skybox_files_name.push_back("back");
		m_file_ext = Constants::NONE;
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

	unsigned int TextureLoaderService::BuildSkyboxTexture(std::string const skybox_path)
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
					std::string const full_path = "resources/skybox/" + skybox_path + "/" + it[0];
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

	unsigned int TextureLoaderService::BuildTexture(std::string const path)
	{

		unsigned int texture_id = 0;
		glGenTextures(1, &texture_id);

		if (texture_id != 0)
		{
			glBindTexture(GL_TEXTURE_2D, texture_id);

			if (glIsTexture(texture_id) == GL_TRUE)
			{
				SDL_Surface* surface = this->LoadTexture(path);
				if (surface != nullptr)
				{
					SDL_Surface* img_invert = this->PixelInverter(surface);
					
					if (img_invert)
					{
						SDL_FreeSurface(surface);
						GLenum intern_format(0);
						GLenum format(0);

						if (img_invert->format->BytesPerPixel == 3) //there is no alpha component
						{
							intern_format = GL_RGB;

							if (img_invert->format->Rmask == 0xff)
							{
								format = GL_RGB;
							}
							else
							{
								format = GL_BGR;
							}
						}
						else if (img_invert->format->BytesPerPixel == 4) //there is one
						{
							intern_format = GL_RGBA;

							if (img_invert->format->Rmask == 0xff)
							{
								format = GL_RGBA;
							}
							else
							{
								format = GL_BGRA;
							}
						}

						glTexImage2D(GL_TEXTURE_2D, 0, intern_format, img_invert->w, img_invert->h, 0, format, GL_UNSIGNED_BYTE, img_invert->pixels);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
						glBindTexture(GL_TEXTURE_2D, 0);

						SDL_FreeSurface(img_invert);
					}
				}
				else
				{
					glDeleteTextures(1, &texture_id);
					texture_id = 0;
				}
			}
		}

		return texture_id;
	}

	SDL_Surface* TextureLoaderService::LoadTexture(std::string path)
	{
		SDL_Surface* surface = nullptr;
		this->FindFileExt(path);
		if (m_file_ext != Constants::NONE)
		{
			path = path + m_file_ext;
			surface = IMG_Load(path.c_str());
			if (surface == nullptr)
			{
				SQ_EXTSERVICE_ERROR("Cannot load texture {} | SDL error : {}", path, SDL_GetError());
			}

			SQ_EXTSERVICE_TRACE("Texture {} load successfully", path);
		}
		

		return surface;
		
	}
	SDL_Surface* TextureLoaderService::PixelInverter(SDL_Surface* src_surface)
	{
		if (src_surface)
		{
			SDL_Surface* img_inverted = SDL_CreateRGBSurface(0, src_surface->w, src_surface->h, src_surface->format->BitsPerPixel, src_surface->format->Rmask,
				src_surface->format->Gmask, src_surface->format->Bmask, src_surface->format->Amask);

			if (img_inverted)
			{
				unsigned char* src_pixels = (unsigned char*)src_surface->pixels;
				unsigned char* inverted_pixels = (unsigned char*)img_inverted->pixels;
				
				for (int i(0); i < src_surface->h; i++)
				{
					for (int j(0); j < src_surface->w * src_surface->format->BytesPerPixel; j++)
					{
						inverted_pixels[(src_surface->w * src_surface->format->BytesPerPixel * (src_surface->h - 1 - i)) + j] = src_pixels[(src_surface->w * src_surface->format->BytesPerPixel * i) + j];
					}

				}
				//==============================================================================================================================

				return img_inverted;
			}
		}
		
		return nullptr;
	}
	void TextureLoaderService::FindFileExt(std::string path)
	{
		std::ifstream flux_in(path + ".jpg");
		m_file_ext = Constants::NONE;
		if (flux_in.is_open())
		{
			///SQ_EXTSERVICE_DEBUG("Extension jpg for {} found", path);
			m_file_ext = ".jpg";
			flux_in.close();
		}
		else
		{
			
			flux_in = std::ifstream(path + ".png");
			if (flux_in.is_open())
			{
				//SQ_EXTSERVICE_DEBUG("Extension png for {} found", path);
				m_file_ext = ".png";
				flux_in.close();
			}
		}
	}
}

