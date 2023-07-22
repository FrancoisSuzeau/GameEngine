/******************************************************************************************************************************************/
// File : ShaderLoaderService.hpp
// Purpose : A service loading glsl files and transorming it in a opengl shader program
/******************************************************************************************************************************************/
#ifndef SHADERLOADERSERVICE_H
#define SHADERLOADERSERVICE_H

#include "IService.hpp"

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Services {

	class ShaderLoaderService : public IService
	{
	public:
		void Init() override;
		void DeInit() override;

		ShaderLoaderService();
		ShaderLoaderService(std::string vertex_path, std::string fragment_path, std::string geometry_path = "NONE");
		~ShaderLoaderService();

		ShaderLoaderService(ShaderLoaderService const& ShaderLoaderService_to_copy);
		ShaderLoaderService& operator=(ShaderLoaderService const& ShaderLoaderService_to_copy);
		void clean();

		GLuint          getProgramID() const;
		bool            loadShader();
		
	private:

		GLuint          m_vertex_ID;
		GLuint          m_fragment_ID;
		GLuint          m_geometry_ID;
		GLuint          m_program_ID;

		std::string     m_vertex_path;
		std::string     m_fragment_path;
		std::string     m_geometry_path = "NONE";

		void            deleteShader(GLuint& shader, GLint detach_shader);
		void            deleteProgram();
		GLint           checkStatus(GLuint obj_id, std::string type);
		bool            compileShader(GLuint& shader, GLenum type, std::string const& file_src);

		
		
	};
}

#endif