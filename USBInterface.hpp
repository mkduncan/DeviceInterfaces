#ifndef USBInterface_H
#define USBInterface_H

#include <SDKDDKVer.h>
#include <boost/asio.hpp>
#include <string>
#include <vector>

class USBInterface
{
private:
	boost::asio::io_service Service;
	boost::asio::windows::stream_handle Stream;
	std::string DevicePath;
	size_t Timeout;

public:
	USBInterface();
	~USBInterface();
	USBInterface(const USBInterface&) = delete;
	USBInterface(USBInterface&&) = delete;
	USBInterface& operator=(const USBInterface&) = delete;
	USBInterface& operator=(USBInterface&&) = delete;

	std::string getDevicePath() const;
	size_t getTimeout() const;

	bool setDevicePath(const std::string&);
	bool setTimeout(const size_t);

	bool openPort();
	bool readData(std::string&, const size_t);
	bool readData(std::vector<uint8_t>&, const size_t);
	bool writeData(const std::string&);
	bool writeData(const std::vector<uint8_t>&);
	bool closePort();
};

#endif