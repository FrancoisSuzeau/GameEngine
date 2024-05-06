/******************************************************************************************************************************************/
// File : Transformer.hpp
// Purpose : The Transformer of all component
/******************************************************************************************************************************************/
#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include "IComponent.hpp"

#include "Services/ShaderService.hpp"
#include "Services/StateService.hpp"

#include "Container/Container.hpp"
#include "Constants/NumberConstants.hpp"
#include "Renderers/Renderers.hpp"

namespace Component
{
	class Transformer
	{
	public:
		static void PutIntoShader(std::shared_ptr<Component::IComponent> component, std::shared_ptr<Services::ShaderService> shader_service, std::string const shader_name);
		static void Move(std::shared_ptr<Component::IComponent> component);
		static void Resize(std::shared_ptr<Component::IComponent> component);
		static void Rotate(std::shared_ptr<Component::IComponent> component, glm::vec3 axis);
		static void ReinitModelMat(std::shared_ptr<Component::IComponent> component);
	private:
		static void PutViewMapIntoShader(std::shared_ptr<Services::ShaderService> shader_service, std::string const shader_name);
	
	};
}

#endif