/******************************************************************************************************************************************/
// File : ShaderService.hpp
// Purpose : A service for communicate between loader and shader
/******************************************************************************************************************************************/
#ifndef SHADERSERVICE_H
#define SHADERSERVICE_H

#include "IService.hpp"
#include "LoaderService.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "OpenGLService.hpp"
#include <iostream>
#include <map>
#include <memory>
#include "Constants/NumberConstants.hpp"
#include "IComponent.hpp"


namespace Services {

	class ShaderService : public IService
	{

	public:
		void Init() override;
		void DeInit() override;
		void AddShader(std::string shader_name, Enums::ShaderType shader_type);
		void DeleteShaderProgram(std::string const shader_program_name);
		void BindShaderProgram(std::string const shader_name);
		void UnbindShaderProgram();

		void BindShaderStorage();
		void UnbindShaderStorage();


		void DeleteBufferStorage();
		void PassLightsParametersToSSBO(std::vector<Light> light_sources);
		void UpdateLightBufferStorage(std::vector<Light> light_sources);

		void            setVec(std::string shader_name, std::string const location, glm::vec3 const& vec_to_add);
		void            setVec(std::string shader_name, std::string const location, glm::vec4 const& vec_to_add);
		void            setMat4(std::string shader_name, std::string const location, glm::mat4 const& matrice_to_add);
		void            setTexture(std::string shader_name, std::string const location, int const count);
		void            setFloat(std::string shader_name, std::string const location, float const to_ad);
		void            setInt(std::string shader_name, std::string const location, int const to_ad);

	private:
		std::shared_ptr<LoaderService> m_loader_service;
		std::shared_ptr<Services::OpenGLService> m_opengl_service;
		std::map<std::string, GLuint> m_shader_program_map;

		GLuint m_ssbo;
	};
}

#endif