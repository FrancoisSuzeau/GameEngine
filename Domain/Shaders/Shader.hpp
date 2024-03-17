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
		Shader(GLuint program_id);
		~Shader();
		GLuint			getProgramId() const;
		void            setVec(std::string const location, glm::vec3 const& vec_to_add);
		void            setVec(std::string const location, glm::vec4 const& vec_to_add);
		void            setMat4(std::string const location, glm::mat4 const& matrice_to_add);
		void            setTexture(std::string const location, int const count);
		void            setFloat(std::string const location, float const to_ad);
		void            setInt(std::string const location, int const to_ad);

		void			deleteProgram();
	private:
		GLuint          m_program_id;
	};
}


#endif