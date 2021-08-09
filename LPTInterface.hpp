#ifndef LPTInterface_H
#define LPTInterface_H

#include <SDKDDKVer.h>
#include <boost/asio.hpp>
#include <string>
#include <vector>

class LPTInterface
{
private:
	boost::asio::io_service Service;
	boost::asio::windows::stream_handle Stream;
	std::string Port;
	size_t Timeout;

public:
	LPTInterface();
	~LPTInterface();
	LPTInterface(const LPTInterface&) = delete;
	LPTInterface(LPTInterface&&) = delete;
	LPTInterface& operator=(const LPTInterface&) = delete;
	LPTInterface& operator=(LPTInterface&&) = delete;

	std::string getPort() const;
	size_t getTimeout() const;

	bool setPort(const std::string&);
	bool setTimeout(const size_t);

	bool openPort();
	bool readData(std::string&, const size_t);
	bool readData(std::vector<uint8_t>&, const size_t);
	bool writeData(const std::string&);
	bool writeData(const std::vector<uint8_t>&);
	bool closePort();
};

#endif