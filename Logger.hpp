#ifndef Logger_H
#define Logger_H

#include <SDKDDKVer.h>
#include <deque>
#include <string>

class Logger
{
private:
	static std::deque<std::string> ErrorLogs;
	static bool Error;

public:
	Logger() = delete;
	~Logger() = delete;
	Logger(const Logger&) = delete;
	Logger(Logger&&) = delete;
	Logger operator=(const Logger&) = delete;
	Logger operator=(Logger&&) = delete;

	static void addErrorLog(const int32_t, const std::string&, const std::string&);
	static void enableErrorLog();
	static void disableErrorLog();
	static void dumpErrorLog(std::string&);
};

#endif