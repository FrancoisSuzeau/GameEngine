/******************************************************************************************************************************************/
// File : JsonLoaderService.hpp
// Purpose : A service loading json files
/******************************************************************************************************************************************/
#ifndef JSONLOADERSERVICE_h
#define JSONLOADERSERVICE_h

#include <chilkat/CkJsonArray.h>
#include <chilkat/CkJsonObject.h>

#include "IService.hpp"

namespace Services {

	class JsonLoaderService : public IService
	{
	public:
		void Init() override;
		void DeInit() override;
	};
}

#endif