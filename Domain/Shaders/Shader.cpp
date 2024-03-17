/******************************************************************************************************************************************/
// File : Shader.cpp
// Purpose : Implementing the shader class
/******************************************************************************************************************************************/

#include "Shader.hpp"

namespace Shaders
{
    Shader::Shader()
    {
    }

    Shader::~Shader()
    {
    }

    void Shader::setVec(GLuint program_id, std::string const location, glm::vec3 const& vec_to_add)
    {
        glUniform3fv(glGetUniformLocation(program_id, location.c_str()), 1, &vec_to_add[0]);
    }

    void Shader::setVec(GLuint program_id, std::string const location, glm::vec4 const& vec_to_add)
    {
        glUniform4fv(glGetUniformLocation(program_id, location.c_str()), 1, &vec_to_add[0]);
    }

    void Shader::setMat4(GLuint program_id, std::string const location, glm::mat4 const& matrice_to_add)
    {
        glUniformMatrix4fv(glGetUniformLocation(program_id, location.c_str()), 1, GL_FALSE, glm::value_ptr(matrice_to_add));
    }

    void Shader::setTexture(GLuint program_id, std::string const location, int const count)
    {
        glUniform1i(glGetUniformLocation(program_id, location.c_str()), count);
    }

    void Shader::setFloat(GLuint program_id, std::string const location, float const to_add)
    {
        glUniform1f(glGetUniformLocation(program_id, location.c_str()), to_add);
    }

    void Shader::setInt(GLuint program_id, std::string const location, int const to_add)
    {
        glUniform1i(glGetUniformLocation(program_id, location.c_str()), to_add);
    }
}


