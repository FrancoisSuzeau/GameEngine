/******************************************************************************************************************************************/
// File : Logger.cpp
// Purpose : Implementation of the wrapper logger
/******************************************************************************************************************************************/
#include "Logger.hpp"


namespace Logger
{

	void Log::InitAllLogger()
	{
		for (auto logger_name : { Constants::CLIENT, Constants::APP, Constants::EXTSERVICE, Constants::SHARED})
		{
			InitTraceLogger(logger_name, Constants::TRACEFILE);
			InitInfoLogger(logger_name, Constants::INFOFILE);
			InitDebugLogger(logger_name, Constants::DEBUGFILE);
			InitWarnLogger(logger_name, Constants::WARNFILE);
			InitErrorLogger(logger_name, Constants::ERRFILE);
			InitCriticalLogger(logger_name, Constants::CRITFILE);
		}
	}

	void Log::Shutdown()
	{
		spdlog::shutdown();
	}

	void Log::InitTraceLogger(std::string const logger_name, std::string const filename)
	{
		auto console = std::make_shared <spdlog::sinks::stdout_color_sink_mt>();
		console->set_level(spdlog::level::trace);
		console->set_pattern(Constants::LOGPATTERN);

		CleanFile(filename);
		auto file_sink = std::make_shared <spdlog::sinks::basic_file_sink_mt>(Constants::LOGPATH + filename + Constants::LOGEXT);
		file_sink->set_level(spdlog::level::trace);
		file_sink->set_pattern(Constants::LOGPATTERN);

		spdlog::sinks_init_list sink_list = { file_sink, console };

		auto logger = std::make_shared<spdlog::logger>(logger_name + filename + "]", sink_list.begin(), sink_list.end());
		logger->set_level(spdlog::level::trace);

		spdlog::register_logger(logger);
	}

	void Log::InitInfoLogger(std::string const logger_name, std::string const filename)
	{
		auto console = std::make_shared <spdlog::sinks::stdout_color_sink_mt>();
		console->set_level(spdlog::level::info);
		console->set_pattern(Constants::LOGPATTERN);

		CleanFile(filename);
		auto file_sink = std::make_shared <spdlog::sinks::basic_file_sink_mt>(Constants::LOGPATH + filename + Constants::LOGEXT);
		file_sink->set_level(spdlog::level::info);
		file_sink->set_pattern(Constants::LOGPATTERN);

		spdlog::sinks_init_list sink_list = { file_sink, console };

		auto logger = std::make_shared<spdlog::logger>(logger_name + filename + "]", sink_list.begin(), sink_list.end());
		logger->set_level(spdlog::level::info);

		spdlog::register_logger(logger);
	}

	void Log::InitDebugLogger(std::string const logger_name, std::string const filename)
	{
		auto console = std::make_shared <spdlog::sinks::stdout_color_sink_mt>();
		console->set_level(spdlog::level::debug);
		console->set_pattern(Constants::LOGPATTERN);

		CleanFile(filename);
		auto file_sink = std::make_shared <spdlog::sinks::basic_file_sink_mt>(Constants::LOGPATH + filename + Constants::LOGEXT);
		file_sink->set_level(spdlog::level::debug);
		file_sink->set_pattern(Constants::LOGPATTERN);

		spdlog::sinks_init_list sink_list = { file_sink, console };

		auto logger = std::make_shared<spdlog::logger>(logger_name + filename + "]", sink_list.begin(), sink_list.end());
		logger->set_level(spdlog::level::debug);

		spdlog::register_logger(logger);
	}

	void Log::InitWarnLogger(std::string const logger_name, std::string const filename)
	{
		auto console = std::make_shared <spdlog::sinks::stdout_color_sink_mt>();
		console->set_level(spdlog::level::warn);
		console->set_pattern(Constants::LOGPATTERN);

		CleanFile(filename);
		auto file_sink = std::make_shared <spdlog::sinks::basic_file_sink_mt>(Constants::LOGPATH + filename + Constants::LOGEXT);
		file_sink->set_level(spdlog::level::warn);
		file_sink->set_pattern(Constants::LOGPATTERN);

		spdlog::sinks_init_list sink_list = { file_sink, console };

		auto logger = std::make_shared<spdlog::logger>(logger_name + filename + "]", sink_list.begin(), sink_list.end());
		logger->set_level(spdlog::level::warn);

		spdlog::register_logger(logger);
	}
	void Log::InitErrorLogger(std::string const logger_name, std::string const filename)
	{
		auto console = std::make_shared <spdlog::sinks::stdout_color_sink_mt>();
		console->set_level(spdlog::level::err);
		console->set_pattern(Constants::LOGPATTERN);

		CleanFile(filename);
		auto file_sink = std::make_shared <spdlog::sinks::basic_file_sink_mt>(Constants::LOGPATH + filename + Constants::LOGEXT);
		file_sink->set_level(spdlog::level::err);
		file_sink->set_pattern(Constants::LOGPATTERN);

		spdlog::sinks_init_list sink_list = { file_sink, console };

		auto logger = std::make_shared<spdlog::logger>(logger_name + filename + "]", sink_list.begin(), sink_list.end());
		logger->set_level(spdlog::level::err);

		spdlog::register_logger(logger);
	}
	void Log::InitCriticalLogger(std::string const logger_name, std::string const filename)
	{
		auto console = std::make_shared <spdlog::sinks::stdout_color_sink_mt>();
		console->set_level(spdlog::level::critical);
		console->set_pattern(Constants::LOGPATTERN);

		CleanFile(filename);
		auto file_sink = std::make_shared <spdlog::sinks::basic_file_sink_mt>(Constants::LOGPATH + filename + Constants::LOGEXT);
		file_sink->set_level(spdlog::level::critical);
		file_sink->set_pattern(Constants::LOGPATTERN);

		spdlog::sinks_init_list sink_list = { file_sink, console };

		auto logger = std::make_shared<spdlog::logger>(logger_name + filename + "]", sink_list.begin(), sink_list.end());
		logger->set_level(spdlog::level::critical);

		spdlog::register_logger(logger);
	}

	void Log::CleanFile(std::string const filename)
	{
		std::ofstream file;
		file.open(Constants::LOGPATH + filename + Constants::LOGEXT, std::ofstream::out | std::ofstream::trunc);
		if (file.is_open())
		{
			file.close();
		}
	}


}