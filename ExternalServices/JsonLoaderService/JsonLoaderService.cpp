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

	void JsonLoaderService::SaveFile(std::string const filename)
	{
		if (!filename.empty())
		{
			std::ofstream flux_out(filename + Constants::JSONEXT);
			if (flux_out.is_open())
			{
				flux_out << "test";
				flux_out.close();
			}
		}
		else
		{
			SQ_EXTSERVICE_ERROR("Class {} in function {} : No filename was given", __FILE__, __FUNCTION__);
		}
	}

	void JsonLoaderService::ReadFile(std::string filename)
	{
		std::ifstream flux_in(filename + Constants::JSONEXT);
		if (flux_in.is_open())
		{
			SQ_EXTSERVICE_TRACE("JSON [{}] file SUCCESSFULLY readed", filename + Constants::JSONEXT);
			if (datas)
			{
				datas.reset();
			}
			datas = std::make_unique<nlohmann::json>(json::parse(flux_in));
			std::string test = GetStringNode(Constants::USERPREFNODE);
		}
		else
		{
			SQ_EXTSERVICE_ERROR("Class {} in function {} : Cannot read or found [{}] file", __FILE__, __FUNCTION__, Constants::CONFIGFILE + Constants::JSONEXT);
		}
	}

	std::string JsonLoaderService::GetStringNode(std::string node_name)
	{
		if (datas)
		{
			std::string node = datas->value(node_name, Constants::NONE);
			if (node == Constants::NONE)
			{
				SQ_EXTSERVICE_ERROR("Class {} in function {} : Cannot found [{}] node", __FILE__, __FUNCTION__, Constants::USERPREFNODE);
				return Constants::NONE;
				
			}

			SQ_EXTSERVICE_TRACE("Node [{}] successfully readed", Constants::USERPREFNODE);
			return node;
		}

		SQ_EXTSERVICE_ERROR("Class {} in function {} : No json was serialized - Cannot read node", __FILE__, __FUNCTION__);
		return Constants::NONE;;
		
	}

}

