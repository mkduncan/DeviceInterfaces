#ifndef LANInterface_H
#define LANInterface_H

#include <SDKDDKVer.h>
#include <boost/asio.hpp>
#include <string>
#include <vector>

class LANInterface
{
private:
	boost::asio::io_service Service;
	boost::asio::ip::tcp::socket Socket;
	std::string Address;
	uint16_t Port;
	size_t Timeout;

public:
	LANInterface();
	~LANInterface();
	LANInterface(const LANInterface&) = delete;
	LANInterface(LANInterface&&) = delete;
	LANInterface& operator=(const LANInterface&) = delete;
	LANInterface& operator=(LANInterface&&) = delete;

	std::string getAddress() const;
	uint16_t getPort() const;
	size_t getTimeout() const;

	bool setAddress(const std::string&);
	bool setPort(const uint16_t);
	bool setTimeout(const size_t);

	bool openPort();
	bool readData(std::string&, const size_t);
	bool readData(std::vector<uint8_t>&, const size_t);
	bool writeData(const std::string&);
	bool writeData(const std::vector<uint8_t>&);
	bool closePort();
};

#endif