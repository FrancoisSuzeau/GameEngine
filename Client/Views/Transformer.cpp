/******************************************************************************************************************************************/
// File : Transformer.cpp
// Purpose : Implementing the transformer 
/******************************************************************************************************************************************/

#include "Transformer.hpp"

namespace Component
{
	void Transformer::PutIntoShader(std::shared_ptr<Renderers::IRenderer> renderer, std::shared_ptr<Services::ShaderService> shader_service, std::string const shader_name)
	{
		if (renderer && shader_service)
		{
			shader_service->setVec3(shader_name, "background_color", renderer->GetBackgroundColor());
			shader_service->setMat4(shader_name, "model", renderer->GetModelMat());
		}
	}

	void Transformer::Move(std::shared_ptr<Renderers::IRenderer> renderer, glm::vec3 new_position)
	{
		if (renderer)
		{
			glm::mat4 model = glm::mat4(1.f);
			model = glm::translate(model, new_position);
			renderer->SetModelMat(model);
		}
	}

	void Transformer::Colorize(std::shared_ptr<Renderers::IRenderer> renderer, glm::vec3 new_color)
	{
		if (renderer)
		{
			renderer->SetBackgroundColor(new_color);
		}
	}
}