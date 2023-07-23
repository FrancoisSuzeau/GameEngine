/******************************************************************************************************************************************/
// File : AudioInitializerService.cpp
// Purpose : Implementing Audio service  Initialisation
/******************************************************************************************************************************************/
#include "AudioInitializerService.hpp"

using namespace Services;

void AudioInitializerService::Init()
{
	init_succeded = true;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        SQ_APP_ERROR("SDL mixer FAILED to initialize - MIX error : {}", Mix_GetError());
		init_succeded = false;
        
    }
	assert(init_succeded);
    SQ_APP_DEBUG("SDL mixer SUCCESSFULLY initialized");
}

void AudioInitializerService::DeInit()
{
	Mix_CloseAudio();
	SQ_APP_DEBUG("SDL mixer process destroyed");
}