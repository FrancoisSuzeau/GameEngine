/******************************************************************************************************************************************/
// File : TextureLoaderService.hpp
// Purpose : A service loading texture files and transorming it in a texture acces memory
/******************************************************************************************************************************************/
#ifndef TEXTURELOADERSERVICE_H
#define TEXTURELOADERSERVICE_H

#include "IService.hpp"

#include <vector>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ConfigEntity.hpp"

#include "Logger.hpp"

namespace Services {

	class TextureLoaderService : public IService
	{
	public:
		void Init() override;
		void DeInit() override;

		TextureLoaderService();

		~TextureLoaderService();

		void BuildSkyboxTexture(std::shared_ptr<ConfigEntity> config);
		unsigned int BuildTexture(std::string const path);

	private:

		SDL_Surface* LoadTexture(std::string path);
		SDL_Surface* PixelInverter(SDL_Surface* src_surface);
		std::vector<std::string> m_skybox_files_name;

	};
}

#endif