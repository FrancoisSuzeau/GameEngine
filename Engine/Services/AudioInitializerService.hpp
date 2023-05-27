/******************************************************************************************************************************************/
// File : AudioInitializerService.hpp
// Purpose : A service initialising SDL_Mixer
/******************************************************************************************************************************************/
#ifndef AINITSERVICE_H
#define AINITSERVICE_H

#include <iostream>
#include <SDL2/SDL_mixer.h>
#include <cassert>
#include <windows.h>

#include "IService.hpp"

namespace Services {

	class AudioInitializerService : public IService
	{
	public:
		void Init();
		void DeInit();

	private:
		void ShowError(std::string error_message);
		bool init_succeded;
		std::string title;
	};
}

#endif