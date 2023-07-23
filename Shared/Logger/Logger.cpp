/******************************************************************************************************************************************/
// File : Logger.cpp
// Purpose : Implementation of the wrapper logger
/******************************************************************************************************************************************/
#include "Logger.hpp"


namespace Logger
{
	std::shared_ptr<spdlog::logger> Log::m_app_logger;
	std::shared_ptr<spdlog::logger> Log::m_client_logger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		m_app_logger = spdlog::stdout_color_mt("APPLICATION");
		m_app_logger->set_level(spdlog::level::trace);
		m_client_logger = spdlog::stdout_color_mt("CLIENT");
		m_client_logger->set_level(spdlog::level::trace);

	}
}