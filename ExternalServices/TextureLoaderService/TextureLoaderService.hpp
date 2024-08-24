/******************************************************************************************************************************************/
// File : TextureLoaderService.hpp
// Purpose : A service loading texture files and transorming it in a texture acces memory
/******************************************************************************************************************************************/
#ifndef TEXTURELOADERSERVICE_H
#define TEXTURELOADERSERVICE_H

#include "IService.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ConfigEntity.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Logger.hpp"

namespace Services {

	class TextureLoaderService : public IService
	{
	public:
		void Init() override;
		void DeInit() override;

		TextureLoaderService();

		~TextureLoaderService();

		unsigned int BuildSkyboxTexture(std::string const skybox_path);
		unsigned int BuildTexture(std::string const path);
		unsigned int BuildTexture(const char* path, const std::string& directory);

	private:

		SDL_Surface* LoadTexture(std::string path);
		SDL_Surface* PixelInverter(SDL_Surface* src_surface);
		void FindFileExt(std::string path);
		std::string m_file_ext;
		std::vector<std::string> m_skybox_files_name;

	};
}

#endif