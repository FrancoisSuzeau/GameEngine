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


namespace Shaders
{
	class Shader
	{
	public:
		Shader();
		~Shader();
		void            setVec(GLuint program_id, std::string const location, glm::vec3 const& vec_to_add);
		void            setVec(GLuint program_id, std::string const location, glm::vec4 const& vec_to_add);
		void            setMat4(GLuint program_id, std::string const location, glm::mat4 const& matrice_to_add);
		void            setTexture(GLuint program_id, std::string const location, int const count);
		void            setFloat(GLuint program_id, std::string const location, float const to_ad);
		void            setInt(GLuint program_id, std::string const location, int const to_ad);
	};
}


#endif