/******************************************************************************************************************************************/
// File : JsonLoaderService.cpp
// Purpose : Implementing JSON loader service
/******************************************************************************************************************************************/
#include "JsonLoaderService.hpp"

namespace Services
{
	using json = nlohmann::json;
	void JsonLoaderService::Init()
	{
		std::ifstream flux_in(Constants::CONFIGFILE + Constants::JSONEXT);
		if (flux_in.is_open())
		{
			config_datas = std::make_unique<nlohmann::json>(json::parse(flux_in));
			SQ_EXTSERVICE_DEBUG("JSON service SUCCESSFULLY initialized");
			std::string node = config_datas->value(Constants::USERPREFNODE, Constants::NONE);
			if (node != Constants::NONE)
			{
				SQ_EXTSERVICE_DEBUG("Node [{}] successfully readed", Constants::USERPREFNODE);
			}
			else
			{
				SQ_EXTSERVICE_ERROR("Cannot found [{}] node", Constants::USERPREFNODE);
			}
		}
		else
		{
			SQ_EXTSERVICE_ERROR("Cannot read or found [{}] file", Constants::CONFIGFILE + Constants::JSONEXT);
		}
	}

	void JsonLoaderService::DeInit()
	{
		SQ_EXTSERVICE_DEBUG("JSON service shutdown");
	}

}

