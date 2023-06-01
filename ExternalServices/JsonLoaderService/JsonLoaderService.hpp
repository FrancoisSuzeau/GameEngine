/******************************************************************************************************************************************/
// File : JsonLoaderService.hpp
// Purpose : A service loading json files
/******************************************************************************************************************************************/
#ifndef JSONLOADERSERVICE_h
#define JSONLOADERSERVICE_h

#include <chilkat/CkJsonArray.h>
#include <chilkat/CkJsonObject.h>
#include <iostream>
#include <fstream>
#include <cassert>

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