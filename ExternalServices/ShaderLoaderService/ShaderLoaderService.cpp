/******************************************************************************************************************************************/
// File : ShaderLoaderService.cpp
// Purpose : Implementing shader loader service
/******************************************************************************************************************************************/
#include "ShaderLoaderService.hpp"

using namespace Services;

void ShaderLoaderService::Init()
{

}

void ShaderLoaderService::DeInit()
{
}

ShaderLoaderService::ShaderLoaderService() : m_vertex_ID(0), m_fragment_ID(0), m_geometry_ID(0), m_program_ID(0), m_vertex_path(), m_fragment_path()
{

}

ShaderLoaderService::~ShaderLoaderService()
{

}

void ShaderLoaderService::clean()
{
	deleteProgram();
}

GLuint ShaderLoaderService::getProgramID() const
{
	return m_program_ID;
}

bool ShaderLoaderService::loadShader(std::string const shader_name, Enums::ShaderType shader_type)
{
	deleteShader(m_vertex_ID, GL_FALSE);
	deleteShader(m_fragment_ID, GL_FALSE);
	if (m_geometry_path != Constants::NONE)
	{
		deleteShader(m_geometry_ID, GL_FALSE);
	}
	deleteProgram();
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
	if (!compileShader(m_vertex_ID, GL_VERTEX_SHADER, m_vertex_path))
	{
		SQ_EXTSERVICE_ERROR("Compiling {} shader FAILED", m_vertex_path);
		return false;
	}
	SQ_EXTSERVICE_TRACE("Compilation success");
	//======================================================================================================================================

	/************************************************* compiling fragment source code ********************************************************/
	SQ_EXTSERVICE_TRACE("Compiling : {}", m_fragment_path);
	if (!compileShader(m_fragment_ID, GL_FRAGMENT_SHADER, m_fragment_path))
	{
		SQ_EXTSERVICE_ERROR("Compiling {} shader FAILED", m_fragment_path);
		return false;
	}
	SQ_EXTSERVICE_TRACE("Compilation success");
	//======================================================================================================================================

	/************************************************* compiling geometry source code ********************************************************/
	if (m_geometry_path != Constants::NONE)
	{
		SQ_EXTSERVICE_TRACE("Compiling : {}", m_geometry_path);
		if (!compileShader(m_geometry_ID, GL_GEOMETRY_SHADER, m_geometry_path))
		{
			SQ_EXTSERVICE_ERROR("Compiling {} shader FAILED", m_geometry_path);
			return false;
		}
		SQ_EXTSERVICE_TRACE("Compilation success");
	}
	//======================================================================================================================================

	/************************************************* creating program for GPU ********************************************************/
	m_program_ID = glCreateProgram();

	//shader association
	glAttachShader(m_program_ID, m_vertex_ID);
	glAttachShader(m_program_ID, m_fragment_ID);
	if (m_geometry_path != Constants::NONE)
	{
		glAttachShader(m_program_ID, m_geometry_ID);
	}
	//======================================================================================================================================

	/**************************************** lock entrees shader (vertices, colors, texture's coordonates *****************************/
	glBindAttribLocation(m_program_ID, 0, "in_Vertex");
	glBindAttribLocation(m_program_ID, 1, "in_Color");
	glBindAttribLocation(m_program_ID, 2, "in_TexCoord0");
	//======================================================================================================================================

	/************************************************* linkage ********************************************************/
	glLinkProgram(m_program_ID);

	//linkage verification
	GLint link_error = checkStatus(m_program_ID, "linking");

	if (link_error != GL_TRUE)//there is an link error
	{
		//size error recovery
		GLint   size_error(0);
		glGetProgramiv(m_program_ID, GL_INFO_LOG_LENGTH, &size_error);

		//memory allocation
		char* error = new char[size_error + 1]; // '\0' character needed

		//error recovery
		glGetShaderInfoLog(m_program_ID, size_error, &size_error, error);
		error[size_error] = '\0';

		//displayiong error message
		SQ_EXTSERVICE_ERROR("Failed to link {} program - Code error : {}", shader_name, error);

		//memory release
		delete[] error;
		deleteProgram();
		deleteShader(m_vertex_ID, link_error);
		deleteShader(m_fragment_ID, link_error);
		if (m_geometry_path != Constants::NONE)
		{
			deleteShader(m_geometry_ID, link_error);
		}

		return false;
	}
	else
	{
		deleteShader(m_vertex_ID, link_error);
		deleteShader(m_fragment_ID, link_error);
		if (m_geometry_path != Constants::NONE)
		{
			deleteShader(m_geometry_ID, link_error);
		}

		SQ_EXTSERVICE_INFO("Successfully linked {} program", shader_name);
		return true;
	}
	//======================================================================================================================================

}

bool ShaderLoaderService::compileShader(GLuint& shader, GLenum type, std::string const& file_src)
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
		deleteShader(shader, false);
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
		deleteShader(shader, false);

		return false;

	}
	else
	{
		return true;
	}
	//======================================================================================================================================

}

void ShaderLoaderService::deleteShader(GLuint& shader, GLint detach_shader)
{
	if (glIsShader(shader) == GL_TRUE)
	{
		if (detach_shader == GL_TRUE)
		{
			glDetachShader(m_program_ID, shader);
		}
		glDeleteShader(shader);
		shader = 0;
	}
}

void ShaderLoaderService::deleteProgram()
{
	if (glIsProgram(m_program_ID) == GL_TRUE)
	{
		glDeleteProgram(m_program_ID);
		m_program_ID = 0;
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