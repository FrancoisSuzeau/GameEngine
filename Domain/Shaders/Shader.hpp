/******************************************************************************************************************************************/
// File : Shader.hpp
// Purpose : The shader that will handle the shadering program
/******************************************************************************************************************************************/
#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Engines
{
	namespace Shaders
	{
		class Shader
		{
		public:
			Shader();
			~Shader();
			GLuint          getProgramID() const;
			void			setProgramID(GLuint const new_program_id);
			void            setVec3(std::string const location, float x, float y, float z);
			void            setVec3(std::string const location, glm::vec3 const& vec_to_add);
			void            setMat4(std::string const location, glm::mat4 const& matrice_to_add);
			void            setTexture(std::string const location, int const count);
			void            setFloat(std::string const location, float const to_ad);
			void            setInt(std::string const location, int const to_ad);
		private:
			GLuint          m_program_id;
		};
	}
}


#endif