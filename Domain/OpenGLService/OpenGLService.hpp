/******************************************************************************************************************************************/
// File : Shader.hpp
// Purpose : The shader that will handle the shadering program
/******************************************************************************************************************************************/
#ifndef OPENGLSERVICE_H
#define OPENGLSERVICE_H

#include <GL/glew.h>
#include <iostream>
#include "../Interfaces/IService.hpp"
#include "../Interfaces/IComponent.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Services
{
	typedef struct
	{
		float position[3];
		float _padding1;
		float inner_color[4];
		int is_textured;
		int mixe_texture_color;
		float constant;
		float linear;
		float quadratic;
		int is_point_light;
		int is_spot_light;
		int is_directional;
		float direction[3];
		float cut_off;
		float outer_cut_off;
		int is_attenuation;
		float intensity;
		float _padding2;
	} Light;

	class OpenGLService: public IService
	{
	public:
		OpenGLService();
		void Init() override;
		void DeInit() override;
		void            setVec(GLuint program_id, std::string const location, glm::vec3 const& vec_to_add);
		void            setVec(GLuint program_id, std::string const location, glm::vec4 const& vec_to_add);
		void            setMat4(GLuint program_id, std::string const location, glm::mat4 const& matrice_to_add);
		void            setTexture(GLuint program_id, std::string const location, int const count);
		void            setFloat(GLuint program_id, std::string const location, float const to_ad);
		void            setInt(GLuint program_id, std::string const location, int const to_ad);
		void setRenderingMode(GLenum const mode, float const line_width);
		void bindProgram(GLuint const program_id);
		void setDepth(GLenum const func);
		void enable(GLenum const cap);
		void blend(GLenum const s_factor, GLenum const d_factor);
		void clearColor(glm::vec4 const colors);
		void disable(GLenum const cap);
		void clearBuffer(GLbitfield const masks);
		void deleteTexture(unsigned int &texture_id);
		void deleteFrameBuffer(unsigned int& buffer_id);
		void deleteBuffer(GLuint& buffer_id);
		void deleteRenderBuffer(unsigned int &render_buffer_id);
		void writeStencilMask(GLuint const mask);
		void stencilFunc(GLenum const func, int const ref, GLuint const mask);

		void generateShaderStorage(GLuint& ssbo, std::vector<Light > lights_sources);
		void updateShaderStorage(GLuint& ssbo, std::vector<Light> lights_sources);
		void bindShaderStorage(GLuint ssbo);
	};
}


#endif