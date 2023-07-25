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
		for (auto filename : {Constants::CONFIGFILE})
		{
			ReadFile(filename);
			SQ_EXTSERVICE_DEBUG("JSON service SUCCESSFULLY initialized");
		}
		
	}

	void JsonLoaderService::DeInit()
	{
		SQ_EXTSERVICE_DEBUG("JSON service shutdown");
	}

	void JsonLoaderService::ReadFile(std::string filename)
	{
		std::ifstream flux_in(filename + Constants::JSONEXT);
		if (flux_in.is_open())
		{
			SQ_EXTSERVICE_TRACE("JSON [{}] file SUCCESSFULLY readed", filename + Constants::JSONEXT);
			datas.reset();
			datas = std::make_unique<nlohmann::json>(json::parse(flux_in));
			std::string test = GetStringNode(Constants::USERPREFNODE);
		}
		else
		{
			SQ_EXTSERVICE_ERROR("Cannot read or found [{}] file", Constants::CONFIGFILE + Constants::JSONEXT);
		}
	}

	std::string JsonLoaderService::GetStringNode(std::string node_name)
	{
		std::string node = datas->value(node_name, Constants::NONE);
		if (node != Constants::NONE)
		{
			SQ_EXTSERVICE_TRACE("Node [{}] successfully readed", Constants::USERPREFNODE);
			return node;
		}
		else
		{
			SQ_EXTSERVICE_ERROR("Cannot found [{}] node", Constants::USERPREFNODE);
			return Constants::NONE;
		}
		
	}

}

