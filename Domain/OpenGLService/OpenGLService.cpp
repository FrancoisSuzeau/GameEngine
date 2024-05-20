/******************************************************************************************************************************************/
// File : OpenGLService.cpp
// Purpose : Implementing the OpenGLService class
/******************************************************************************************************************************************/

#include "OpenGLService.hpp"

namespace Services
{
    OpenGLService::OpenGLService()
    {
    }

    void OpenGLService::Init()
    {
        
    }

    void OpenGLService::DeInit()
    {
    }

    

    void OpenGLService::setVec(GLuint program_id, std::string const location, glm::vec3 const& vec_to_add)
    {
        glUniform3fv(glGetUniformLocation(program_id, location.c_str()), 1, &vec_to_add[0]);
    }

    void OpenGLService::setVec(GLuint program_id, std::string const location, glm::vec4 const& vec_to_add)
    {
        glUniform4fv(glGetUniformLocation(program_id, location.c_str()), 1, &vec_to_add[0]);
    }

    void OpenGLService::setMat4(GLuint program_id, std::string const location, glm::mat4 const& matrice_to_add)
    {
        glUniformMatrix4fv(glGetUniformLocation(program_id, location.c_str()), 1, GL_FALSE, glm::value_ptr(matrice_to_add));
    }

    void OpenGLService::setTexture(GLuint program_id, std::string const location, int const count)
    {
        glUniform1i(glGetUniformLocation(program_id, location.c_str()), count);
    }

    void OpenGLService::setFloat(GLuint program_id, std::string const location, float const to_add)
    {
        glUniform1f(glGetUniformLocation(program_id, location.c_str()), to_add);
    }

    void OpenGLService::setInt(GLuint program_id, std::string const location, int const to_add)
    {
        glUniform1i(glGetUniformLocation(program_id, location.c_str()), to_add);
    }
    void OpenGLService::setRenderingMode(GLenum const mode, float const line_width)
    {
        glLineWidth(line_width);
        glPolygonMode(GL_FRONT_AND_BACK, mode);
    }

    void OpenGLService::bindProgram(GLuint const program_id)
    {
        glUseProgram(program_id);
    }

    void OpenGLService::setDepth(GLenum const func)
    {
        glDepthFunc(func);
    }

    void OpenGLService::enable(GLenum const cap)
    {
        glEnable(cap);
    }
    void OpenGLService::blend(GLenum const s_factor, GLenum const d_factor)
    {
        glBlendFunc(s_factor, d_factor);
    }

    void OpenGLService::clearColor(glm::vec4 const colors)
    {
        glClearColor(colors.x, colors.y, colors.z, colors.a);
    }

    void OpenGLService::disable(GLenum const cap)
    {
        glDisable(cap);
    }

    void OpenGLService::clearBuffer(GLbitfield const masks)
    {
        glClear(masks);
    }

    void OpenGLService::deleteTexture(unsigned int texture_id)
    {
        if (texture_id != 0)
        {
            glDeleteTextures(1, &texture_id);
        }
    }

    void OpenGLService::deleteBuffer(unsigned int buffer_id)
    {
        if (buffer_id != 0)
        {
            glDeleteFramebuffers(1, &buffer_id);
        }
    }

    void OpenGLService::deleteRenderBuffer(unsigned int render_buffer_id)
    {
        if (render_buffer_id != 0)
        {
            glDeleteRenderbuffers(1, &render_buffer_id);
        }
    }

    void OpenGLService::writeStencilMask(GLuint const mask)
    {
        glStencilMask(mask);
    }

    void OpenGLService::stencilFunc(GLenum const func, int const ref, GLuint const mask)
    {
        glStencilFunc(func, ref, mask);
    }


}


