#include "COMInterface.hpp"
#include "Logger.hpp"
#include "Utility.hpp"
#include <algorithm>
#include <regex>
#include <set>

COMInterface::COMInterface() : Service(), Stream(this->Service), Configuration({ 0 }), Port(), Timeout(Utility::DEFAULT_TIMEOUT), Bluetooth(false)
{
}

COMInterface::~COMInterface()
{
	this->closePort();
	this->Configuration = { 0 };
	this->Port.clear();
	this->Timeout = Utility::DEFAULT_TIMEOUT;
	this->Bluetooth = false;
}

uint32_t COMInterface::getBaudRate() const
{
	return this->Configuration.dcb.BaudRate;
}

uint8_t COMInterface::getByteSize() const
{
	return this->Configuration.dcb.ByteSize;
}

uint8_t COMInterface::getParity() const
{
	return this->Configuration.dcb.Parity;
}

std::string COMInterface::getPort() const
{
	return this->Port;
}

uint8_t COMInterface::getStopBits() const
{
	return this->Configuration.dcb.StopBits;
}

size_t COMInterface::getTimeout() const
{
	return this->Timeout;
}

bool COMInterface::setBaudRate(const uint32_t baudRate)
{
	static const std::set<uint32_t> baudRates({ 75, 110, 134, 150, 300, 600, 1200, 1800, 2400, 4800, 7200, 9600, 14400, 19200, 38400, 57600, 115200, 128000 });

	if (baudRates.find(baudRate) == baudRates.end())
	{
		Logger::addErrorLog(__LINE__, std::string("COMInterface::setBaudRate()"), std::string("Selected unsupported baud rate = ") + std::to_string(baudRate));
		return false;
	}

	this->Configuration.dcb.BaudRate = baudRate;
	return true;
}

bool COMInterface::setByteSize(const uint8_t byteSize)
{
	if (byteSize < 4 || byteSize > 8)
	{
		Logger::addErrorLog(__LINE__, std::string("COMInterface::setByteSize()"), std::string("Selected unsupported byte size = ") + std::to_string(byteSize));
		return false;
	}

	this->Configuration.dcb.ByteSize = byteSize;
	return true;
}

bool COMInterface::setParity(const uint8_t parity)
{
	if (parity > 2)
	{
		Logger::addErrorLog(__LINE__, std::string("COMInterface::setParity()"), std::string("Selected unsupported parity = ") + std::to_string(parity));
		return false;
	}

	this->Configuration.dcb.Parity = parity;
	return true;
}

bool COMInterface::setPort(const std::string& port)
{
	static const std::regex match(std::string("^COM([1-9]|[1-8][0-9]|9[0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$"));
	static const std::string registryPath("HARDWARE\\DEVICEMAP\\SERIALCOMM"), registryValue("BTHMODE");
	HKEY registryKey;
	std::string value(0x3FFF, '\0'), data(0x3FFF, '\0'), portName(port.size(), '\0');
	DWORD totalValues, errorCode, valueLength = static_cast<DWORD>(value.size()), dataLength = static_cast<DWORD>(data.size());
	long portNumber = 0;

	std::transform(port.begin(), port.end(), portName.begin(), ::toupper);

	if (!std::regex_match(portName, match))
	{
		Logger::addErrorLog(__LINE__, std::string("COMInterface::setPort()"), std::string("Selected invalid port name = ") + portName);
		return false;
	}

	this->Port = portName;
	this->Configuration.dwSize = sizeof(COMMCONFIG);
	this->Bluetooth = false;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, registryPath.c_str(), 0, KEY_READ, &registryKey) == ERROR_SUCCESS)
	{
		errorCode = RegQueryInfoKey(registryKey, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &totalValues, nullptr, nullptr, nullptr, nullptr);

		for (DWORD index = 0; index < totalValues; ++index)
		{
			valueLength = 0xFF;
			value[0] = '\0';
			errorCode = RegEnumValue(registryKey, index, &value[0], &valueLength, nullptr, nullptr, reinterpret_cast<LPBYTE>(&data[0]), &dataLength);

			value.resize(valueLength);
			data.resize(dataLength);
			std::transform(value.begin(), value.end(), value.begin(), ::toupper);
			std::transform(data.begin(), data.end(), data.begin(), ::toupper);

			if (errorCode == ERROR_SUCCESS && value.find(registryValue) != std::string::npos && data == Port)
			{
				this->Bluetooth = true;
				break;
			}
		}
	}

	RegCloseKey(registryKey);

	if (!this->Bluetooth && (!GetDefaultCommConfig(this->Port.c_str(), &this->Configuration, &this->Configuration.dwSize) || this->Configuration.dwSize != sizeof(COMMCONFIG)))
	{
		this->Configuration = { 0 };

		Logger::addErrorLog(__LINE__, std::string("COMInterface::setPort()"), std::string("Failed to retrieve system default configuration for port name = ") + portName);
		Logger::addErrorLog(__LINE__, std::string("COMInterface::setPort()"), std::string("System reported error code = ") + std::to_string(::GetLastError()));

		return false;
	}

	else if (this->Bluetooth)
	{
		this->Configuration.dcb.BaudRate = 115200;
		this->Configuration.dcb.ByteSize = 8;
		this->Configuration.dcb.Parity = NOPARITY;
		this->Configuration.dcb.StopBits = 0;
	}

	return true;
}

bool COMInterface::setStopBits(const uint8_t stopBits)
{
	if (stopBits > 2)
	{
		Logger::addErrorLog(__LINE__, std::string("COMInterface::setStopBits()"), std::string("Selected unsupported stop bits = ") + std::to_string(stopBits));
		return false;
	}

	Configuration.dcb.StopBits = stopBits;
	return true;
}

bool COMInterface::setTimeout(const size_t timeout)
{
	this->Timeout = timeout;
	return true;
}

bool COMInterface::isBluetooth() const
{
	return this->Bluetooth;
}

bool COMInterface::openPort()
{
	static const std::string path("\\\\.\\");
	const std::string portName(path + this->Port);
	COMMTIMEOUTS timeouts = { MAXDWORD, 0, 0, 0, 0 };
	HANDLE handle = INVALID_HANDLE_VALUE;
	DWORD errorCode;

	if (!this->closePort())
	{
		Logger::addErrorLog(__LINE__, std::string("COMInterface::openPort()"), std::string("Failed to close previously opened COM port."));
		return false;
	}

	handle = ::CreateFile(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING | FILE_FLAG_WRITE_THROUGH | FILE_FLAG_OVERLAPPED, nullptr);

	if (handle == INVALID_HANDLE_VALUE)
	{
		Logger::addErrorLog(__LINE__, std::string("COMInterface::openPort()"), std::string("Failed to open file handle for port = ") + this->Port);
		Logger::addErrorLog(__LINE__, std::string("COMInterface::openPort()"), std::string("System reported error code = ") + std::to_string(::GetLastError()));

		return false;
	}

	else if (!::SetCommState(handle, &Configuration.dcb))
	{
		errorCode = ::GetLastError();
		::PurgeComm(handle, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);
		::SetCommTimeouts(handle, &timeouts);
		::CloseHandle(handle);

		Logger::addErrorLog(__LINE__, std::string("COMInterface::openPort()"), std::string("Failed to set interface settings for port = ") + this->Port);
		Logger::addErrorLog(__LINE__, std::string("COMInterface::openPort()"), std::string("System reported error code = ") + std::to_string(errorCode));

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

		Logger::addErrorLog(__LINE__, std::string("COMInterface::openPort()"), std::string("Failed to create asychronous stream handler for port = ") + this->Port);
		Logger::addErrorLog(__LINE__, std::string("COMInterface::openPort()"), std::string("System reported error code = ") + std::to_string(exception.code().value()));

		return false;
	}

	return true;
}

bool COMInterface::readData(std::string& data, const size_t size)
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

		Logger::addErrorLog(__LINE__, std::string("COMInterface::readData()"), std::string("Failed to allocate memory."));
		return false;
	}

	else if (!Utility::readBytes(this->Service, this->Stream, &data[0], bytes, this->Timeout))
	{
		data.resize(bytes);

		if(bytes != 0 && data.size() != bytes)
			Logger::addErrorLog(__LINE__, std::string("COMInterface::readData()"), std::string("Failed to allocate memory."));

		else if (data.empty())
			Logger::addErrorLog(__LINE__, std::string("COMInterface::readData()"), std::string("Failed to read any requested data for port = ") + this->Port);

		return false;
	}

	return true;
}

bool COMInterface::readData(std::vector<uint8_t>& data, const size_t size)
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

		Logger::addErrorLog(__LINE__, std::string("COMInterface::readData()"), std::string("Failed to allocate memory."));
		return false;
	}

	else if (!Utility::readBytes(this->Service, this->Stream, &data[0], bytes, this->Timeout))
	{
		data.resize(bytes);

		if (bytes != 0 && data.size() != bytes)
			Logger::addErrorLog(__LINE__, std::string("COMInterface::readData()"), std::string("Failed to allocate memory."));

		else if (data.empty())
			Logger::addErrorLog(__LINE__, std::string("COMInterface::readData()"), std::string("Failed to read requested data for port = ") + this->Port);

		return false;
	}

	return true;
}

bool COMInterface::writeData(const std::string& data)
{
	if (!data.empty() && !Utility::writeBytes(this->Service, this->Stream, &data[0], data.size(), this->Timeout))
	{
		Logger::addErrorLog(__LINE__, std::string("COMInterface::writeData()"), std::string("Failed to write requested data for port = ") + this->Port);
		return false;
	}

	return true;
}

bool COMInterface::writeData(const std::vector<uint8_t>& data)
{
	if (!data.empty() && !Utility::writeBytes(this->Service, this->Stream, &data[0], data.size(), this->Timeout))
	{
		Logger::addErrorLog(__LINE__, std::string("COMInterface::writeData()"), std::string("Failed to write requested data for port = ") + this->Port);
		return false;
	}

	return true;
}

bool COMInterface::closePort()
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
		Logger::addErrorLog(__LINE__, std::string("COMInterface::closePort()"), std::string("Failed to close previously opened asychronous stream handle."));
		Logger::addErrorLog(__LINE__, std::string("COMInterface::closePort()"), std::string("System reported error code = ") + std::to_string(exception.code().value()));

		return false;
	}

	return true;
}