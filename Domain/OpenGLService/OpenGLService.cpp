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

    void OpenGLService::deleteTexture(unsigned int &texture_id)
    {
        if (texture_id != 0)
        {
            glDeleteTextures(1, &texture_id);
            texture_id = 0;
        }
    }

    void OpenGLService::deleteFrameBuffer(unsigned int &buffer_id)
    {
        if (buffer_id != 0)
        {
            glDeleteFramebuffers(1, &buffer_id);
            buffer_id = 0;
        }
    }

    void OpenGLService::deleteBuffer(GLuint& buffer_id)
    {
        if (buffer_id != 0)
        {
            glDeleteBuffers(1, &buffer_id);
            buffer_id = 0;
        }
    }

    void OpenGLService::deleteRenderBuffer(unsigned int &render_buffer_id)
    {
        if (render_buffer_id != 0)
        {
            glDeleteRenderbuffers(1, &render_buffer_id);
            render_buffer_id = 0;
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

    void OpenGLService::generateShaderStorage(GLuint& ssbo, std::vector<Light> lights_sources)
    {
        if (ssbo == 0)
        {
            glGenBuffers(1, &ssbo);
        }

        size_t bytes_light_sources = sizeof(Light) * lights_sources.size();

        if (ssbo != 0)
        {
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
            if (glIsBuffer(ssbo) == GL_TRUE)
            {

                glBufferData(GL_SHADER_STORAGE_BUFFER, bytes_light_sources, 0, GL_DYNAMIC_COPY);

                // Fill SSBO with data
                glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, bytes_light_sources, lights_sources.data());

                glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
            }

        }
    }

    void OpenGLService::updateShaderStorage(GLuint& ssbo, std::vector<Light> lights_sources)
    {
        size_t bytes_light_sources = sizeof(Light) * lights_sources.size();

        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
        void* ptr = glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, bytes_light_sources, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
        if (ptr) {
            memcpy(ptr, lights_sources.data(), bytes_light_sources);
            glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
        }

        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    void OpenGLService::bindShaderStorage(GLuint ssbo)
    {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
    }
}


