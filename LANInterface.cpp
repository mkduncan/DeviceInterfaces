#include "LANInterface.hpp"
#include "Logger.hpp"
#include "Utility.hpp"
#include <regex>

LANInterface::LANInterface() : Service(), Socket(this->Service), Address(), Port(0), Timeout(Utility::DEFAULT_TIMEOUT)
{
}

LANInterface::~LANInterface()
{
	this->closePort();
	this->Address.clear();
	this->Port = 0;
	this->Timeout = Utility::DEFAULT_TIMEOUT;
}

std::string LANInterface::getAddress() const
{
	return this->Address;
}

uint16_t LANInterface::getPort() const
{
	return this->Port;
}

size_t LANInterface::getTimeout() const
{
	return this->Timeout;
}

bool LANInterface::setAddress(const std::string& address)
{
	static const std::regex match(std::string("^(?:(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])(\\.(?!$)|$)){4}$"));

	if (!std::regex_match(address, match))
	{
		Logger::addErrorLog(__LINE__, std::string("LANInterface::setAddress()"), std::string("Selected invalid IPv4 address = ") + address);
		return false;
	}

	this->Address = address;
	return true;
}

bool LANInterface::setPort(const uint16_t port)
{
	if (port == 0)
	{
		Logger::addErrorLog(__LINE__, std::string("LANInterface::setPort()"), std::string("Selected invalid IPv4 port number = ") + std::to_string(port));
		return false;
	}

	this->Port = port;
	return true;
}

bool LANInterface::setTimeout(const size_t timeout)
{
	this->Timeout = timeout;
	return true;
}

bool LANInterface::openPort()
{
	if (!this->closePort())
	{
		Logger::addErrorLog(__LINE__, std::string("LANInterface::openPort()"), std::string("Failed to close previously opened LAN port."));
		return false;
	}

	try
	{
		this->Socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(this->Address), this->Port));
	}

	catch (const boost::system::system_error& exception)
	{
		this->closePort();

		Logger::addErrorLog(__LINE__, std::string("LANInterface::openPort()"), std::string("Failed to create asychronous stream handler for IPv4 address = ") + this->Address + std::string(":") + std::to_string(this->Port));
		Logger::addErrorLog(__LINE__, std::string("LANInterface::openPort()"), std::string("System reported error code = ") + std::to_string(exception.code().value()));

		return false;
	}

	return true;
}

bool LANInterface::readData(std::string& data, const size_t size)
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

		Logger::addErrorLog(__LINE__, std::string("LANInterface::readData()"), std::string("Failed to allocate memory."));
		return false;
	}

	else if (!Utility::readBytes(this->Service, this->Socket, &data[0], bytes, this->Timeout))
	{
		data.resize(bytes);

		if (bytes != 0 && data.size() != bytes)
			Logger::addErrorLog(__LINE__, std::string("LANInterface::readData()"), std::string("Failed to allocate memory."));

		else if (data.empty())
			Logger::addErrorLog(__LINE__, std::string("LANInterface::readData()"), std::string("Failed to read any requested data for IPv4 address = ") + this->Address + std::string(":") + std::to_string(this->Port));

		return false;
	}

	return true;
}

bool LANInterface::readData(std::vector<uint8_t>& data, const size_t size)
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

		Logger::addErrorLog(__LINE__, std::string("LANInterface::readData()"), std::string("Failed to allocate memory."));
		return false;
	}

	else if (!Utility::readBytes(this->Service, this->Socket, &data[0], bytes, this->Timeout))
	{
		data.resize(bytes);

		if (bytes != 0 && data.size() != bytes)
			Logger::addErrorLog(__LINE__, std::string("LANInterface::readData()"), std::string("Failed to allocate memory."));

		else if (data.empty())
			Logger::addErrorLog(__LINE__, std::string("LANInterface::readData()"), std::string("Failed to read any requested data for IPv4 address = ") + this->Address + std::string(":") + std::to_string(this->Port));

		return false;
	}

	return true;
}

bool LANInterface::writeData(const std::string& data)
{
	if (!data.empty() && !Utility::writeBytes(this->Service, this->Socket, &data[0], data.size(), this->Timeout))
	{
		Logger::addErrorLog(__LINE__, std::string("LANInterface::writeData()"), std::string("Failed to write requested data for IPv4 address = ") + this->Address + std::string(":") + std::to_string(this->Port));
		return false;
	}

	return true;
}

bool LANInterface::writeData(const std::vector<uint8_t>& data)
{
	if (!data.empty() && !Utility::writeBytes(this->Service, this->Socket, &data[0], data.size(), this->Timeout))
	{
		Logger::addErrorLog(__LINE__, std::string("LANInterface::writeData()"), std::string("Failed to write requested data for IPv4 address = ") + this->Address + std::string(":") + std::to_string(this->Port));
		return false;
	}

	return true;
}

bool LANInterface::closePort()
{
	try
	{
		if (Socket.is_open())
		{
			Socket.close();
		}
	}

	catch (const boost::system::system_error& exception)
	{
		Logger::addErrorLog(__LINE__, std::string("LANInterface::closePort()"), std::string("Failed to close previously opened asychronous stream handle."));
		Logger::addErrorLog(__LINE__, std::string("LANInterface::closePort()"), std::string("System reported error code = ") + std::to_string(exception.code().value()));

		return false;
	}

	return true;
}