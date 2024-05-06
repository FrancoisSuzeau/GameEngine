/******************************************************************************************************************************************/
// File : KeyboardInputService.hpp
// Purpose : A service to handle keyboard input
/******************************************************************************************************************************************/
#ifndef KEYBOARDINPUTSERVICE_H
#define KEYBOARDINPUTSERVICE_H

#include "IService.hpp"
#include "CameraService.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Services {

	class KeyboardInputService : public IService
	{

	public:
		void Init() override;
		void DeInit() override;
		void Update(SDL_Event event);
		bool* GetKeys();

	private:
		bool        m_keys[SDL_NUM_SCANCODES];
		std::shared_ptr<CameraService> m_camera_service;
	};
}

#endif