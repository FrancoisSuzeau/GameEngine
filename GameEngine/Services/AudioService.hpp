/******************************************************************************************************************************************/
// File : AudioService.hpp
// Purpose : A service initialising SDL_Mixer
/******************************************************************************************************************************************/
#ifndef AUDIOSERVICE_H
#define AUDIOSERVICE_H

#include <iostream>
#include <SDL2/SDL_mixer.h>

#include "IService.hpp"

namespace Services {

	class AudioService : public IService
	{
	public:
		void Init() override;
		void DeInit() override;

	private:
		void ShowError(std::string error_message) override;
	};
}

#endif