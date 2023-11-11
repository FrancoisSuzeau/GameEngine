/******************************************************************************************************************************************/
// File : Transformer.hpp
// Purpose : The Transformer of all component
/******************************************************************************************************************************************/
#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include "IComponent.hpp"
#include "Services/Services.hpp"
#include "Container/Container.hpp"
#include "Constants/NumberConstants.hpp"
#include "Renderers/Renderers.hpp"

namespace Component
{
	class Transformer
	{
	public:
		static void PutIntoShader(std::shared_ptr<Renderers::IRenderer> renderer, std::shared_ptr<Services::ShaderService> shader_service, std::string const shader_name);
		static void Move(std::shared_ptr<Renderers::IRenderer> renderer, glm::vec3 new_position);
		static void Resize(std::shared_ptr<Renderers::IRenderer> renderer, glm::vec3 size_vector);
		static void Rotate(std::shared_ptr<Renderers::IRenderer> renderer, float angle, glm::vec3 axis);
		static void ReinitModelMat(std::shared_ptr<Renderers::IRenderer> renderer);
	private:
		static void PutViewMapIntoShader(std::shared_ptr<Services::StateService> state_service, std::shared_ptr<Services::ShaderService> shader_service, std::string const shader_name);
	
	};
}

#endif