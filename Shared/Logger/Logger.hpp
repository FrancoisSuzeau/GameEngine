/******************************************************************************************************************************************/
// File : Logger.hpp
// Purpose : A wrapper logger using the spdlog github project
/******************************************************************************************************************************************/
#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "../Crosscutting/Constants/StringConstants.hpp"

namespace Logger
{
	class Log
	{
	public:
		static void InitAllLogger();
		static void Shutdown();
	private: 
		static void InitTraceLogger(std::string const logger_name, std::string const filename);
		static void InitDebugLogger(std::string const logger_name, std::string const filename);
		static void InitWarnLogger(std::string const logger_name, std::string const filename);
		static void InitErrorLogger(std::string const logger_name, std::string const filename);
		static void InitCriticalLogger(std::string const logger_name, std::string const filename);
		static void CleanFile(std::string const filename);
	};
}
#define CLIENTNAME(a, b) a + b

// Client logs macros
#define SQ_CLIENT_TRACE(...) if(spdlog::get(Constants::CLIENT + Constants::TRACEFILE  + "]") != nullptr) {spdlog::get(Constants::CLIENT + Constants::TRACEFILE  + "]")->trace(__VA_ARGS__);}
#define SQ_CLIENT_DEBUG(...) if(spdlog::get(Constants::CLIENT + Constants::DEBUGFILE  + "]") != nullptr) {spdlog::get(Constants::CLIENT + Constants::DEBUGFILE  + "]")->debug(__VA_ARGS__);}
#define SQ_CLIENT_WARN(...) if(spdlog::get(Constants::CLIENT + Constants::WARNFILE + "]") != nullptr) {spdlog::get(Constants::CLIENT + Constants::WARNFILE + "]")->warn(__VA_ARGS__);}
#define SQ_CLIENT_ERROR(...) if(spdlog::get(Constants::CLIENT + Constants::ERRFILE + "]") != nullptr) {spdlog::get(Constants::CLIENT + Constants::ERRFILE  + "]")->error(__VA_ARGS__);}
#define SQ_CLIENT_CRITICAL(...) if(spdlog::get(Constants::CLIENT + Constants::CRITFILE  + "]") != nullptr) {spdlog::get(Constants::CLIENT + Constants::CRITFILE + "]")->critical(__VA_ARGS__);}

// App logs macros

#define SQ_APP_TRACE(...) if(spdlog::get(Constants::APP + Constants::TRACEFILE  + "]") != nullptr) {spdlog::get(Constants::APP + Constants::TRACEFILE + "]")->trace(__VA_ARGS__);}
#define SQ_APP_DEBUG(...) if(spdlog::get(Constants::APP + Constants::DEBUGFILE  + "]") != nullptr) {spdlog::get(Constants::APP + Constants::DEBUGFILE + "]")->debug(__VA_ARGS__);}
#define SQ_APP_WARN(...) if(spdlog::get(Constants::APP + Constants::WARNFILE  + "]") != nullptr) {spdlog::get(Constants::APP + Constants::WARNFILE + "]")->warn(__VA_ARGS__);}
#define SQ_APP_ERROR(...) if(spdlog::get(Constants::APP + Constants::ERRFILE  + "]") != nullptr) {spdlog::get(Constants::APP + Constants::ERRFILE + "]")->error(__VA_ARGS__);}
#define SQ_APP_CRITICAL(...) if(spdlog::get(Constants::APP + Constants::CRITFILE + "]") != nullptr) {spdlog::get(Constants::APP + Constants::CRITFILE + "]")->critical(__VA_ARGS__);}

#endif