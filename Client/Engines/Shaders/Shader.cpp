/******************************************************************************************************************************************/
// File : Shader.cpp
// Purpose : Implementing the shader class
/******************************************************************************************************************************************/

#include "Shader.hpp"

using namespace Engines::Shaders;

Shader::Shader()
{
}

Shader::~Shader()
{
}

GLuint Shader::getProgramID() const
{
	return m_program_id;
}

void Shader::setProgramID(GLuint const new_program_id)
{
	m_program_id = new_program_id;
}

void Shader::setVec3(std::string const location, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(m_program_id, location.c_str()), x, y, z);
}

void Shader::setVec3(std::string const location, glm::vec3 const& vec_to_add)
{
    glUniform3fv(glGetUniformLocation(m_program_id, location.c_str()), 1, &vec_to_add[0]);
}

void Shader::setMat4(std::string const location, glm::mat4 const& matrice_to_add)
{
    glUniformMatrix4fv(glGetUniformLocation(m_program_id, location.c_str()), 1, GL_FALSE, glm::value_ptr(matrice_to_add));
}

void Shader::setTexture(std::string const location, int const count)
{
    glUniform1i(glGetUniformLocation(m_program_id, location.c_str()), count);
}

void Shader::setFloat(std::string const location, float const to_add)
{
    glUniform1f(glGetUniformLocation(m_program_id, location.c_str()), to_add);
}

void Shader::setInt(std::string const location, int const to_add)
{
    glUniform1i(glGetUniformLocation(m_program_id, location.c_str()), to_add);
}
