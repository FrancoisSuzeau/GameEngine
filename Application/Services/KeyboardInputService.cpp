/******************************************************************************************************************************************/
// File : KeyboardInputService.cpp
// Purpose : Implementing the mouse picker service
/******************************************************************************************************************************************/
#include "KeyboardInputService.hpp"

namespace Services
{
	void KeyboardInputService::Init()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_camera_service = container->GetReference<CameraService>();

			if (!m_camera_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Camera service is not referenced yet", __FILE__, __FUNCTION__);
			}
		}

		for (int i(0); i < SDL_NUM_SCANCODES; i++)
		{
			m_keys[i] = false;
		}
	}

	void KeyboardInputService::DeInit()
	{
		if (m_camera_service)
		{
			m_camera_service.reset();
		}
	}
	void KeyboardInputService::Update(SDL_Event event)
	{
		switch (event.type)
		{
			//activate a key
		case SDL_KEYDOWN:
			m_keys[event.key.keysym.scancode] = true;
			break;
		case SDL_KEYUP:
			m_keys[event.key.keysym.scancode] = false;
			break;
		default:
			break;
		}
	}
	bool* KeyboardInputService::GetKeys()
	{
		return m_keys;
	}
}

