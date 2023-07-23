/******************************************************************************************************************************************/
// File : AudioInitializerService.hpp
// Purpose : A service initialising SDL_Mixer
/******************************************************************************************************************************************/
#ifndef AINITSERVICE_H
#define AINITSERVICE_H

#include <SDL2/SDL_mixer.h>
#include <cassert>
#include <string>
#include "Logger.hpp"

#include "IService.hpp"

namespace Services {

	class AudioInitializerService : public IService
	{
	public:
		void Init();
		void DeInit();

	private:
		bool init_succeded;
	};
}

#endif