#include "hzpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Hazel
{

/*static*/ std::shared_ptr<spdlog::logger> Log::sCoreLogger;
/*static*/ std::shared_ptr<spdlog::logger> Log::sClientLogger;

void Log::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");

	sCoreLogger = spdlog::stdout_color_mt("HAZEL");
	sCoreLogger->set_level(spdlog::level::trace);

	sClientLogger = spdlog::stdout_color_mt("APP");
	sClientLogger->set_level(spdlog::level::trace);
}
}
