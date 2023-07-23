/******************************************************************************************************************************************/
// File : JsonLoaderService.hpp
// Purpose : A service loading json files
/******************************************************************************************************************************************/
#ifndef JSONLOADERSERVICE_H
#define JSONLOADERSERVICE_H

#include <chilkat/CkJsonArray.h>
#include <chilkat/CkJsonObject.h>
#include <fstream>
#include <cassert>
#include "Constants/StringConstants.hpp"
//#include "Logger.hpp"

#include "IService.hpp"

namespace Services {

	class JsonLoaderService : public IService
	{
	public:
		void Init() override;
		void DeInit() override;
	private:
		CkJsonObject *all_file = nullptr;
	};
}

#endif