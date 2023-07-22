/******************************************************************************************************************************************/
// File : SceneEngine.hpp
// Purpose : The Scene engine of the application
/******************************************************************************************************************************************/

#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <string>

#include "../Shaders/Shader.hpp"

namespace Engines
{
	namespace SceneEngine
	{
		class SceneEngine
		{
		public:
			void addShader(std::string shader_name, GLuint program_id);
			void deleteShader(std::string shader_name);
		private:
			std::map < std::string, std::unique_ptr<Shaders::Shader>> m_shader_map;
		};
	}
}


#endif