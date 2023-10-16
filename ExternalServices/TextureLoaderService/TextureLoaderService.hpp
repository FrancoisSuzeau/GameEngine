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

#include "Logger.hpp"

namespace Services {

	class TextureLoaderService : public IService
	{
	public:
		void Init() override;
		void DeInit() override;

		TextureLoaderService();

		~TextureLoaderService();


		unsigned int BuildSkyboxTexture(std::string const repository_path);
		void DestroyTexture(unsigned int texture_id);

	private:

		SDL_Surface* LoadTexture(std::string path);
		unsigned int texture_id;

		std::vector<std::string> m_skybox_files_name;

	};
}

#endif