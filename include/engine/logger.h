
#pragma once

#include <string>
#include <fstream>

#include "others.h"

static std::string m_logName = "log/log.txt";
static std::ofstream m_logFile;
static bool m_initialized = false;
static bool m_consoleOutput;

namespace logger
{
	enum class LEVEL { INFO, WARN, OK, ERROR };

	void log(const std::string& text, logger::LEVEL report)
	{
		if (m_logFile.is_open())
		{
			std::string state;

			switch (report)
			{
			case LEVEL::INFO:
				state = "[  INFO ]";
				break;
			case LEVEL::WARN:
				state = "[  WARN ]";
				break;
			case LEVEL::OK:
				state = "[  OK   ]";
				break;
			case LEVEL::ERROR:
				state = "[ ERROR ]";
				break;
			}

			m_logFile << "[ " << engine::utilities::others::time::getTime() << " ]" << state << ": " << text << '\n';
		}
	}

	void init(bool toConsole = false)
	{
		if (m_initialized)
			return;

		m_consoleOutput = toConsole;

		m_logFile.open(m_logName, std::ios_base::app);

		m_initialized = true;

		logger::log("--- NEW SESSION ---", logger::LEVEL::INFO);
		logger::log("Logger initialized", logger::LEVEL::OK);
	}
}