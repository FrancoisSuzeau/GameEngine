/******************************************************************************************************************************************/
// File : JsonLoaderService.cpp
// Purpose : Implementing JSON loader service
/******************************************************************************************************************************************/
#include "JsonLoaderService.hpp"

using namespace Services;

void JsonLoaderService::Init()
{
	//std::ifstream flux_in(Constants::CONFIGFILE + Constants::JSONEXT);
	//if (flux_in && all_file == nullptr)
	//{
	//	all_file = new CkJsonObject();
 //		assert(all_file);
	//	bool load_success = all_file->Load(std::string((std::istreambuf_iterator<char>(flux_in)), std::istreambuf_iterator<char>()).c_str());
	//	assert(load_success);
	//	flux_in.close();
	//	//SQ_EXTSERVICE_DEBUG("JSON service SUCCESSFULLY initialized");
	//}
}

void JsonLoaderService::DeInit()
{
	/*if (all_file != nullptr)
	{
		delete all_file;
		all_file = nullptr;
	}*/
	//SQ_EXTSERVICE_DEBUG("JSON service shutdown");
}
