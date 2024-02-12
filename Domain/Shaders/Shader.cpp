/******************************************************************************************************************************************/
// File : Shader.cpp
// Purpose : Implementing the shader class
/******************************************************************************************************************************************/

#include "Shader.hpp"

namespace Shaders
{
    Shader::Shader(GLuint program_id) : m_program_id(program_id)
    {
    }

    Shader::~Shader()
    {
    }

    GLuint Shader::getProgramId() const
    {
        return m_program_id;
    }

    void Shader::setVec(std::string const location, glm::vec3 const& vec_to_add)
    {
        glUniform3fv(glGetUniformLocation(m_program_id, location.c_str()), 1, &vec_to_add[0]);
    }

    void Shader::setVec(std::string const location, glm::vec4 const& vec_to_add)
    {
        glUniform4fv(glGetUniformLocation(m_program_id, location.c_str()), 1, &vec_to_add[0]);
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
}


