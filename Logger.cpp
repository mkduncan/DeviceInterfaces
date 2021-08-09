#include "Logger.hpp"
#include "Utility.hpp"

static std::string Buffer = std::string();
std::deque<std::string> Logger::ErrorLogs({ "Initialization of error logger. This message should be at the header." });
bool Logger::Error = false;

void Logger::addErrorLog(const int32_t line, const std::string& method, const std::string& message)
{
	if (Logger::Error)
	{
		Buffer.append(Utility::getDateTime());
		Buffer.append(std::string(" Error: encountered problem in method "));
		Buffer.append(method);
		Buffer.append(std::string(" at line "));
		Buffer.append(std::to_string(line));
		Buffer.append(std::string(" - "));
		Buffer.append(message);
		ErrorLogs.push_back(Buffer);
		Buffer.clear();

		if (ErrorLogs.size() > (Utility::MAX_LOGGING_SIZE >> 1))
			ErrorLogs.pop_front();
	}
}

void Logger::enableErrorLog()
{
	Logger::Error = true;
}

void Logger::disableErrorLog()
{
	Logger::Error = false;
}

void Logger::dumpErrorLog(std::string& data)
{
	if (!Logger::ErrorLogs.empty())
	{
		data.clear();

		while (!Logger::ErrorLogs.empty())
		{
			Buffer.append(ErrorLogs.front() + std::string("\r\n"));
			ErrorLogs.pop_front();
		}

		std::swap(data, Buffer);
	}
}
