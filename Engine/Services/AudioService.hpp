/******************************************************************************************************************************************/
// File : AudioService.hpp
// Purpose : A service initialising SDL_Mixer
/******************************************************************************************************************************************/
#ifndef AUDIOSERVICE_H
#define AUDIOSERVICE_H

#include <iostream>
#include <SDL2/SDL_mixer.h>
#include <cassert>
#include <windows.h>

namespace Services {

	class AudioService
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