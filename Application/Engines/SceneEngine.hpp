/******************************************************************************************************************************************/
// File : SceneEngine.hpp
// Purpose : The Scene engine of the application
/******************************************************************************************************************************************/

#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <string>
#include "../Builders/ViewModelBuilder.hpp"

#include "../Shaders/Shader.hpp"
#include "IEngine.hpp"
#include "Constants/StringConstants.hpp"

namespace Engines
{
	class SceneEngine : public IEngine
	{
	public:
		void Construct() override;

		void RenderScene(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder);
		
	private:
		void InitFrame() override;
		void EndFrame() override;
		std::map < std::string, std::unique_ptr<Shaders::Shader>> m_shader_map;
	};
}


#endif