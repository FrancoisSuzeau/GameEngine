/******************************************************************************************************************************************/
// File : SceneEngine.hpp
// Purpose : The Scene engine of the application
/******************************************************************************************************************************************/

#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <string>

#include "../Shaders/Shader.hpp"
#include "IEngine.hpp"

namespace Engines
{
	class SceneEngine : public IEngine
	{
	public:
		void Construct() override;
		
	private:
		void InitFrame() override;
		void EndFrame() override;
		std::map < std::string, std::unique_ptr<Shaders::Shader>> m_shader_map;
	};
}


#endif