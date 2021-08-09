#define WIN32_LEAN_AND_MEAN

#include "LPTInterface.hpp"
#include "Logger.hpp"
#include "Utility.hpp"
#include <algorithm>
#include <regex>
#include <windows.h>

LPTInterface::LPTInterface() : Service(), Stream(this->Service), Port(), Timeout(Utility::DEFAULT_TIMEOUT)
{
}

LPTInterface::~LPTInterface()
{
	this->closePort();
	this->Port.clear();
	this->Timeout = Utility::DEFAULT_TIMEOUT;
}

std::string LPTInterface::getPort() const
{
	return this->Port;
}

size_t LPTInterface::getTimeout() const
{
	return this->Timeout;
}

bool LPTInterface::setPort(const std::string& port)
{
	static const std::regex match(std::string("^LPT([1-9]|[1-8][0-9]|9[0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$"));
	std::string portName(port.size(), '\0');

	std::transform(port.begin(), port.end(), portName.begin(), ::toupper);

	if (!std::regex_match(portName, match))
	{
		Logger::addErrorLog(__LINE__, std::string("LPTInterface::setPort()"), std::string("Selected invalid port name = ") + portName);
		return false;
	}

	this->Port = portName;
	return true;
}

bool LPTInterface::setTimeout(const size_t timeout)
{
	this->Timeout = timeout;
	return true;
}

bool LPTInterface::openPort()
{
	static const std::string path("\\\\.\\");
	const std::string portName(path + this->Port);
	HANDLE handle = INVALID_HANDLE_VALUE;

	if (!this->closePort())
	{
		Logger::addErrorLog(__LINE__, std::string("LPTInterface::openPort()"), std::string("Failed to close previously opened LPT port."));
		return false;
	}

	handle = ::CreateFile(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING | FILE_FLAG_WRITE_THROUGH | FILE_FLAG_OVERLAPPED, nullptr);

	if (handle == INVALID_HANDLE_VALUE)
	{
		Logger::addErrorLog(__LINE__, std::string("LPTInterface::openPort()"), std::string("Failed to open file handle for port = ") + this->Port);
		Logger::addErrorLog(__LINE__, std::string("LPTInterface::openPort()"), std::string("System reported error code = ") + std::to_string(::GetLastError()));

		return false;
	}

	try
	{
		this->Stream = boost::asio::windows::stream_handle(this->Service, handle);
	}

	catch (const boost::system::system_error& exception)
	{
		::CloseHandle(handle);
		this->closePort();

		Logger::addErrorLog(__LINE__, std::string("LPTInterface::openPort()"), std::string("Failed to set interface settings for port = ") + this->Port);
		Logger::addErrorLog(__LINE__, std::string("LPTInterface::openPort()"), std::string("System reported error code = ") + std::to_string(exception.code().value()));

		return false;
	}

	return true;
}

bool LPTInterface::readData(std::string& data, const size_t size)
{
	size_t bytes = size;

	if (bytes == 0)
	{
		return true;
	}

	data.resize(bytes, '\0');

	if (data.size() != bytes)
	{
		data.clear();

		Logger::addErrorLog(__LINE__, std::string("LPTInterface::readData()"), std::string("Failed to allocate memory."));
		return false;
	}

	else if (!Utility::readBytes(this->Service, this->Stream, &data[0], bytes, this->Timeout))
	{
		data.resize(bytes);

		if (bytes != 0 && data.size() != bytes)
			Logger::addErrorLog(__LINE__, std::string("LPTInterface::readData()"), std::string("Failed to allocate memory."));

		else if (data.empty())
			Logger::addErrorLog(__LINE__, std::string("LPTInterface::readData()"), std::string("Failed to read any requested data for port = ") + this->Port);

		return false;
	}

	return true;
}

bool LPTInterface::readData(std::vector<uint8_t>& data, const size_t size)
{
	size_t bytes = size;

	if (bytes == 0)
	{
		return true;
	}

	data.resize(bytes, '\0');

	if (data.size() != bytes)
	{
		data.clear();

		Logger::addErrorLog(__LINE__, std::string("LPTInterface::readData()"), std::string("Failed to allocate memory."));
		return false;
	}

	else if (!Utility::readBytes(this->Service, this->Stream, &data[0], bytes, this->Timeout))
	{
		data.resize(bytes);

		if (bytes != 0 && data.size() != bytes)
			Logger::addErrorLog(__LINE__, std::string("LPTInterface::readData()"), std::string("Failed to allocate memory."));

		else if (data.empty())
			Logger::addErrorLog(__LINE__, std::string("LPTInterface::readData()"), std::string("Failed to read any requested data for port = ") + this->Port);

		return false;
	}

	return true;
}

bool LPTInterface::writeData(const std::string& data)
{
	if (!data.empty() && !Utility::writeBytes(this->Service, this->Stream, &data[0], data.size(), this->Timeout))
	{
		Logger::addErrorLog(__LINE__, std::string("LPTInterface::writeData()"), std::string("Failed to write requested data for port = ") + this->Port);
		return false;
	}

	return true;
}

bool LPTInterface::writeData(const std::vector<uint8_t>& data)
{
	if (!data.empty() && !Utility::writeBytes(this->Service, this->Stream, &data[0], data.size(), this->Timeout))
	{
		Logger::addErrorLog(__LINE__, std::string("LPTInterface::writeData()"), std::string("Failed to write requested data for port = ") + this->Port);
		return false;
	}

	return true;
}

bool LPTInterface::closePort()
{
	try
	{
		if (this->Stream.is_open())
		{
			this->Stream.close();
		}
	}

	catch (const boost::system::system_error& exception)
	{
		Logger::addErrorLog(__LINE__, std::string("LPTInterface::closePort()"), std::string("Failed to close previously opened asychronous stream handle."));
		Logger::addErrorLog(__LINE__, std::string("LPTInterface::closePort()"), std::string("System reported error code = ") + std::to_string(exception.code().value()));

		return false;
	}

	return true;
}