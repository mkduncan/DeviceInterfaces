#define WIN32_LEAN_AND_MEAN

#include "USBInterface.hpp"
#include "Logger.hpp"
#include "Utility.hpp"
#include <regex>
#include <windows.h>

USBInterface::USBInterface() : Service(), Stream(this->Service), DevicePath(), Timeout(Utility::DEFAULT_TIMEOUT)
{
}

USBInterface::~USBInterface()
{
	this->closePort();
	this->DevicePath.clear();
	this->Timeout = Utility::DEFAULT_TIMEOUT;
}

std::string USBInterface::getDevicePath() const
{
	return this->DevicePath;
}

size_t USBInterface::getTimeout() const
{
	return this->Timeout;
}

bool USBInterface::setDevicePath(const std::string& devicePath)
{
	static const std::regex match(std::string("^\\\\\\\\[?]\\\\USB#VID_[0-9A-F]{4}&PID_[0-9A-F]{4}#.*#[{][0-9A-F]{8}-[0-9A-F]{4}-[0-9A-F]{4}-[0-9A-F]{4}-[0-9A-F]{12}[}]$"));
	std::string port(devicePath.size(), '\0');

	std::transform(devicePath.begin(), devicePath.end(), port.begin(), ::toupper);

	if (!std::regex_match(devicePath, match))
	{
		Logger::addErrorLog(__LINE__, std::string("USBInterface::setPort()"), std::string("Selected invalid device path name = ") + port);
		return false;
	}

	this->DevicePath = port;
	return true;
}

bool USBInterface::setTimeout(const size_t timeout)
{
	this->Timeout = timeout;
	return true;
}

bool USBInterface::openPort()
{
	static const std::string pipe("\\PIPE00");
	const std::string port(this->DevicePath + pipe);
	HANDLE handle = INVALID_HANDLE_VALUE;

	if (!this->closePort())
	{
		Logger::addErrorLog(__LINE__, std::string("USBInterface::openPort()"), std::string("Failed to close previously opened USB port."));
		return false;
	}

	handle = CreateFile(port.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, nullptr);

	if (handle == INVALID_HANDLE_VALUE)
	{
		Logger::addErrorLog(__LINE__, std::string("USBInterface::openPort()"), std::string("Failed to open file handle for device path name = ") + this->DevicePath);
		Logger::addErrorLog(__LINE__, std::string("USBInterface::openPort()"), std::string("System reported error code = ") + std::to_string(::GetLastError()));

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

		Logger::addErrorLog(__LINE__, std::string("USBInterface::openPort()"), std::string("Failed to set interface settings for device path name = ") + this->DevicePath);
		Logger::addErrorLog(__LINE__, std::string("USBInterface::openPort()"), std::string("System reported error code = ") + std::to_string(exception.code().value()));

		return false;
	}

	return true;
}

bool USBInterface::readData(std::string& data, const size_t size)
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

		Logger::addErrorLog(__LINE__, std::string("USBInterface::readData()"), std::string("Failed to allocate memory."));
		return false;
	}

	else if (!Utility::readBytes(this->Service, this->Stream, &data[0], bytes, this->Timeout))
	{
		data.resize(bytes);

		if (bytes != 0 && data.size() != bytes)
			Logger::addErrorLog(__LINE__, std::string("USBInterface::readData()"), std::string("Failed to allocate memory."));

		else if (data.empty())
			Logger::addErrorLog(__LINE__, std::string("USBInterface::readData()"), std::string("Failed to read any requested data for device path name = ") + this->DevicePath);

		return false;
	}

	return true;
}

bool USBInterface::readData(std::vector<uint8_t>& data, const size_t size)
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

		Logger::addErrorLog(__LINE__, std::string("USBInterface::readData()"), std::string("Failed to allocate memory."));
		return false;
	}

	else if (!Utility::readBytes(this->Service, this->Stream, &data[0], bytes, this->Timeout))
	{
		data.resize(bytes);

		if (bytes != 0 && data.size() != bytes)
			Logger::addErrorLog(__LINE__, std::string("USBInterface::readData()"), std::string("Failed to allocate memory."));

		else if (data.empty())
			Logger::addErrorLog(__LINE__, std::string("USBInterface::readData()"), std::string("Failed to read any requested data for device path name = ") + this->DevicePath);

		return false;
	}

	return true;
}

bool USBInterface::writeData(const std::string& data)
{
	if (!data.empty() && !Utility::writeBytes(this->Service, this->Stream, &data[0], data.size(), this->Timeout))
	{
		Logger::addErrorLog(__LINE__, std::string("USBInterface::writeData()"), std::string("Failed to write requested data for device path name = ") + this->DevicePath);
		return false;
	}

	return true;
}

bool USBInterface::writeData(const std::vector<uint8_t>& data)
{
	if (!data.empty() && !Utility::writeBytes(this->Service, this->Stream, &data[0], data.size(), this->Timeout))
	{
		Logger::addErrorLog(__LINE__, std::string("USBInterface::writeData()"), std::string("Failed to write requested data for device path name = ") + this->DevicePath);
		return false;
	}

	return true;
}

bool USBInterface::closePort()
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