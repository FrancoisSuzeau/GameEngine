/******************************************************************************************************************************************/
// File : ShaderService.hpp
// Purpose : A service for communicate between loader and shader
/******************************************************************************************************************************************/
#ifndef SHADERSERVICE_H
#define SHADERSERVICE_H

#include "IService.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "ExternalServices.hpp"
#include "Shader.hpp"
#include <iostream>
#include <map>
#include <memory>
#include "Constants/NumberConstants.hpp"

namespace Services {

	class ShaderService : public IService
	{

	public:
		void Init() override;
		void DeInit() override;
		void LoadShader(std::string shader_name, Enums::ShaderType shader_type);
		void DeleteShader(std::string shader_name);
		GLuint GetProgramId(std::string const shader_name);

		void            setVec3(std::string shader_name, std::string const location, glm::vec3 const& vec_to_add);
		void            setMat4(std::string shader_name, std::string const location, glm::mat4 const& matrice_to_add);
		void            setTexture(std::string shader_name, std::string const location, int const count);
		void            setFloat(std::string shader_name, std::string const location, float const to_ad);
		void            setInt(std::string shader_name, std::string const location, int const to_ad);

	private:
		std::shared_ptr<Services::ShaderLoaderService> m_shader_loader;
		std::map<std::string, std::unique_ptr<Shaders::Shader>> m_shader_map;
	};
}

#endif