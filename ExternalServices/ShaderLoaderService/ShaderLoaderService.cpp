/******************************************************************************************************************************************/
// File : ShaderLoaderService.cpp
// Purpose : Implementing shader loader service
/******************************************************************************************************************************************/
#include "ShaderLoaderService.hpp"

namespace Services
{
	void ShaderLoaderService::Init()
	{

	}

	void ShaderLoaderService::DeInit()
	{
	}

	ShaderLoaderService::ShaderLoaderService() : m_vertex_ID(0), m_fragment_ID(0), m_geometry_ID(0), m_vertex_path(), m_fragment_path()
	{

	}

	ShaderLoaderService::~ShaderLoaderService()
	{

	}

	GLuint ShaderLoaderService::loadShader(std::string const shader_name, Enums::ShaderType shader_type)
	{
		GLuint program_id = 0;
		deleteShader(m_vertex_ID, GL_FALSE, program_id);
		deleteShader(m_fragment_ID, GL_FALSE, program_id);
		if (m_geometry_path != Constants::NONE)
		{
			deleteShader(m_geometry_ID, GL_FALSE, program_id);
		}
		deleteProgram(program_id);
		m_vertex_path = Constants::SHADERSPATH + shader_name + Constants::SHADERVERTEXT;
		m_fragment_path = Constants::SHADERSPATH + shader_name + Constants::SHADERFRAGEXT;
		if (shader_type == Enums::ShaderType::GEOMETRIC)
		{
			m_geometry_path = Constants::SHADERSPATH + shader_name + Constants::SHADERGEOEXT;
		}
		else
		{
			m_geometry_path = Constants::NONE;
		}
		/************************************************* compiling shader source code ********************************************************/
		SQ_EXTSERVICE_TRACE("Compiling : {}", m_vertex_path);
		if (!compileShader(m_vertex_ID, GL_VERTEX_SHADER, m_vertex_path, program_id))
		{
			SQ_EXTSERVICE_ERROR("Compiling {} shader FAILED", m_vertex_path);
			return 0;
		}
		SQ_EXTSERVICE_TRACE("Compilation success");
		//======================================================================================================================================

		/************************************************* compiling fragment source code ********************************************************/
		SQ_EXTSERVICE_TRACE("Compiling : {}", m_fragment_path);
		if (!compileShader(m_fragment_ID, GL_FRAGMENT_SHADER, m_fragment_path, program_id))
		{
			SQ_EXTSERVICE_ERROR("Compiling {} shader FAILED", m_fragment_path);
			return 0;
		}
		SQ_EXTSERVICE_TRACE("Compilation success");
		//======================================================================================================================================

		/************************************************* compiling geometry source code ********************************************************/
		if (m_geometry_path != Constants::NONE)
		{
			SQ_EXTSERVICE_TRACE("Compiling : {}", m_geometry_path);
			if (!compileShader(m_geometry_ID, GL_GEOMETRY_SHADER, m_geometry_path, program_id))
			{
				SQ_EXTSERVICE_ERROR("Compiling {} shader FAILED", m_geometry_path);
				return 0;
			}
			SQ_EXTSERVICE_TRACE("Compilation success");
		}
		//======================================================================================================================================

		/************************************************* creating program for GPU ********************************************************/
		program_id = glCreateProgram();

		//shader association
		glAttachShader(program_id, m_vertex_ID);
		glAttachShader(program_id, m_fragment_ID);
		if (m_geometry_path != Constants::NONE)
		{
			glAttachShader(program_id, m_geometry_ID);
		}
		//======================================================================================================================================

		/**************************************** lock entrees shader (vertices, colors, texture's coordonates *****************************/
		glBindAttribLocation(program_id, 0, "obj_pos");
		//======================================================================================================================================

		/************************************************* linkage ********************************************************/
		glLinkProgram(program_id);

		//linkage verification
		GLint link_error = checkStatus(program_id, "linking");

		if (link_error != GL_TRUE)//there is an link error
		{
			//size error recovery
			GLint   size_error(0);
			glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &size_error);

			//memory allocation
			char* error = new char[size_error + 1]; // '\0' character needed

			//error recovery
			glGetShaderInfoLog(program_id, size_error, &size_error, error);
			error[size_error] = '\0';

			//displayiong error message
			SQ_EXTSERVICE_ERROR("Failed to link {} program - Code error : {}", shader_name, error);

			//memory release
			delete[] error;
			deleteProgram(program_id);
			deleteShader(m_vertex_ID, link_error, program_id);
			deleteShader(m_fragment_ID, link_error, program_id);
			if (m_geometry_path != Constants::NONE)
			{
				deleteShader(m_geometry_ID, link_error, program_id);
			}

			return 0;
		}
		else
		{
			deleteShader(m_vertex_ID, link_error, program_id);
			deleteShader(m_fragment_ID, link_error, program_id);
			if (m_geometry_path != Constants::NONE)
			{
				deleteShader(m_geometry_ID, link_error, program_id);
			}

			SQ_EXTSERVICE_INFO("Successfully linked {} program", shader_name);
			return program_id;
		}
		//======================================================================================================================================

	}

	bool ShaderLoaderService::compileShader(GLuint& shader, GLenum type, std::string const& file_src, GLuint program_id)
	{
		std::string shader_type;
		switch (type)
		{
		case GL_VERTEX_SHADER:
			shader_type = "vertex shader";
			break;
		case GL_FRAGMENT_SHADER:
			shader_type = "fragment shader";
			break;
		case GL_GEOMETRY_SHADER:
			shader_type = "geometry shader";
			break;
		default:
			break;
		}

		/************************************************* creating shader/fragment ********************************************************/
		shader = glCreateShader(type);
		if (shader == 0)
		{
			SQ_EXTSERVICE_ERROR("({}) type creation failed", shader_type);
			return false;
		}
		//======================================================================================================================================

		/************************************************* read flow ********************************************************/
		std::ifstream file(file_src.c_str());
		if (!file.is_open())
		{
			SQ_EXTSERVICE_ERROR("Unable to read file : {}", file_src);
			deleteShader(shader, false, program_id);
			return false;
		}

		//======================================================================================================================================


		/************************************************* copying src code ********************************************************/
		std::string line;
		std::string src_code;

		while (std::getline(file, line))
		{
			src_code += line + '\n';
		}
		file.close();
		//============================================================================================================================

		/************************************************* compile shader ********************************************************/
		//string C recovery by source code
		const GLchar* string_src_code = src_code.c_str();

		//send source code to shader
		glShaderSource(shader, 1, &string_src_code, NULL);

		//compile shader
		glCompileShader(shader);
		//======================================================================================================================================

		/************************************************* compile verification ********************************************************/
		//status recovery
		GLint   compile_error = checkStatus(shader, "compiling");
		if (compile_error != GL_TRUE) //there is an error
		{
			//size error recovery
			GLint error_size(0);
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &error_size);

			//memory allocation
			char* error = new char[error_size + 1]; //need the '\0' character

			//error recovery
			glGetShaderInfoLog(shader, error_size, &error_size, error);
			error[error_size] = '\0';

			//error displaying
			SQ_EXTSERVICE_ERROR("Compilation FAILED - Code error : {}", error);

			//memory release
			delete[] error;
			deleteShader(shader, false, program_id);

			return false;

		}
		else
		{
			return true;
		}
		//======================================================================================================================================

	}

	void ShaderLoaderService::deleteShader(GLuint& shader, GLint detach_shader, GLuint program_id)
	{
		if (glIsShader(shader) == GL_TRUE)
		{
			if (detach_shader == GL_TRUE)
			{
				glDetachShader(program_id, shader);
				SQ_EXTSERVICE_TRACE("Detach shader");
			}
			glDeleteShader(shader);
			SQ_EXTSERVICE_TRACE("Delete shader");
			shader = 0;
		}
	}

	void ShaderLoaderService::deleteProgram(GLuint program_id)
	{
		if (glIsProgram(program_id) == GL_TRUE)
		{
			glDeleteProgram(program_id);
			SQ_EXTSERVICE_TRACE("Delete program");
			program_id = 0;
		}
	}

	GLint ShaderLoaderService::checkStatus(GLuint obj_id, std::string type)
	{
		GLint error(0);

		if (type == "linking")
		{
			glGetProgramiv(obj_id, GL_LINK_STATUS, &error);
		}

		if (type == "compiling")
		{
			glGetShaderiv(obj_id, GL_COMPILE_STATUS, &error);
		}

		return error;
	}
}

