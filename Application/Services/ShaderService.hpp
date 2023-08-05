/******************************************************************************************************************************************/
// File : ShaderService.hpp
// Purpose : A service for communicate between loader and shader
/******************************************************************************************************************************************/
#ifndef SHADERSERVICE_H
#define SHADERSERVICE_H

#include "IService.hpp"
#include "Logger.hpp"

namespace Services {

	class ShaderService : public IService
	{

	public:
		void Init() override;
		void DeInit() override;


	private:
		
	};
}

#endif