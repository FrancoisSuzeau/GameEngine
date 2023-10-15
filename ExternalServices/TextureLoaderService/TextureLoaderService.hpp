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


		unsigned int LoadTexture(std::vector<std::string> faces_path);
		void DestroyTexture(unsigned int texture_id);

	private:

		SDL_Surface* LoadFile(std::string path);
		unsigned int texture_id;

	};
}

#endif