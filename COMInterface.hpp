#ifndef COMInterface_H
#define COMInterface_H

#define WIN32_LEAN_AND_MEAN

#include <SDKDDKVer.h>
#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <windows.h>

class COMInterface
{
private:
	boost::asio::io_service Service;
	boost::asio::windows::stream_handle Stream;
	COMMCONFIG Configuration;
	std::string Port;
	size_t Timeout;
	bool Bluetooth;

public:
	COMInterface();
	~COMInterface();
	COMInterface(const COMInterface&) = delete;
	COMInterface(COMInterface&&) = delete;
	COMInterface& operator=(const COMInterface&) = delete;
	COMInterface& operator=(COMInterface&&) = delete;

	uint32_t getBaudRate() const;
	uint8_t getByteSize() const;
	uint8_t getParity() const;
	std::string getPort() const;
	uint8_t getStopBits() const;
	size_t getTimeout() const;

	bool setBaudRate(const uint32_t);
	bool setByteSize(const uint8_t);
	bool setParity(const uint8_t);
	bool setPort(const std::string&);
	bool setStopBits(const uint8_t);
	bool setTimeout(const size_t);

	bool isBluetooth() const;

	bool openPort();
	bool readData(std::string&, const size_t);
	bool readData(std::vector<uint8_t>&, const size_t);
	bool writeData(const std::string&);
	bool writeData(const std::vector<uint8_t>&);
	bool closePort();
};

#endif