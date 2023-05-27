/******************************************************************************************************************************************/
// File : AudioService.cpp
// Purpose : Implementing Audio service  Initialisation
/******************************************************************************************************************************************/
#include "AudioService.hpp"

using namespace Services;

void AudioService::Init()
{
	init_succeded = true;
	title = "Audio Services Initialization";
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        std::string error_message = "Cannot initialize SDL mixer with param : 44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024\n";
        ShowError(error_message);
    }
	assert(init_succeded);
    std::cout << ">> Initialise SDL mixer : SUCCESS" << std::endl;
}

void AudioService::DeInit()
{
	title = "Graphic Services De-initialization";
	Mix_CloseAudio();
	std::cout << ">> SDL mixer service destroyed" << std::endl;
}

void AudioService::ShowError(std::string error_message)
{
	std::string sdl_error(Mix_GetError());
	if (sdl_error != "")
	{
		error_message.append("SDL Error : ");
		error_message.append(sdl_error.c_str());
		error_message.append("\n");
	}

	MessageBoxA(0, error_message.c_str(), title.c_str(), MB_ICONERROR | MB_OK);
	init_succeded = false;
}
