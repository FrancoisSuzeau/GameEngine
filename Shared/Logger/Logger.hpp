/******************************************************************************************************************************************/
// File : Logger.hpp
// Purpose : A wrapper logger using the spdlog github project
/******************************************************************************************************************************************/
#ifndef LOGGER_H
#define LOGGER_H

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Logger
{
	class Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return m_app_logger; };
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_client_logger; };
	private:
		static std::shared_ptr<spdlog::logger> m_app_logger;
		static std::shared_ptr<spdlog::logger> m_client_logger;
	};
}

// App log macros
#define SQ_APP_ERROR(...)		::Logger::Log::GetAppLogger()->error(__VA_ARGS__)
#define SQ_APP_WARN(...)		::Logger::Log::GetAppLogger()->warn(__VA_ARGS__)
#define SQ_APP_INFO(...)		::Logger::Log::GetAppLogger()->info(__VA_ARGS__)
#define SQ_APP_TRACE(...)		::Logger::Log::GetAppLogger()->trace(__VA_ARGS__)
#define SQ_APP_FATAL(...)		::Logger::Log::GetAppLogger()->fatal(__VA_ARGS__)
#define SQ_CLIENT_TRACE(...)	::Logger::Log::GetClientLogger()->trace(__VA_ARGS__)
// Client log macros
#define SQ_CLIENT_ERROR(...)	::Logger::Log::GetClientLogger()->error(__VA_ARGS__)
#define SQ_CLIENT_WARN(...)		::Logger::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SQ_CLIENT_INFO(...)		::Logger::Log::GetClientLogger()->info(__VA_ARGS__)
#define SQ_CLIENT_TRACE(...)	::Logger::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SQ_CLIENT_FATAL(...)	::Logger::Log::GetClientLogger()->fatal(__VA_ARGS__)


#endif