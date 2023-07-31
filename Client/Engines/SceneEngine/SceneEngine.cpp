/******************************************************************************************************************************************/
// File : SceneEngine.cpp
// Purpose : Implementing the scene engine where object will be rendered
/******************************************************************************************************************************************/
#include "SceneEngine.hpp"

namespace Engines 
{
	namespace SceneEngine
	{
		void SceneEngine::Construct()
		{
		}

		void SceneEngine::addShader(std::string shader_name, GLuint program_id)
		{
			m_shader_map.insert_or_assign(shader_name, std::make_unique<Shaders::Shader>());
			m_shader_map.at(shader_name)->setProgramID(program_id);
		}

		void SceneEngine::deleteShader(std::string shader_name)
		{
			m_shader_map.at(shader_name).reset();
			m_shader_map.erase(shader_name);
		}
		void SceneEngine::InitFrame()
		{
		}
		void SceneEngine::EndFrame()
		{
		}
	}
	
}


