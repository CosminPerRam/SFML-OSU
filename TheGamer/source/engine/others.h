
#pragma once

#include <ctime>
#include <iomanip>
#include <chrono>
#include <string>

namespace engine::utilities::others
{
	namespace time
	{
		std::string getDate(const time_t& now = std::time(0))
		{
			tm ltm;
			localtime_s(&ltm, &now);

			return std::to_string(1900 + ltm.tm_year) + "-" + std::to_string(1 + ltm.tm_mon) + "-" + std::to_string(ltm.tm_mday);
		}

		std::string getTime(const time_t& now = std::time(0))
		{
			tm ltm;
			localtime_s(&ltm, &now);

			return std::to_string(1 + ltm.tm_hour) + ":" + std::to_string(1 + ltm.tm_min) + ":" + std::to_string(1 + ltm.tm_sec);
		}
	}
}