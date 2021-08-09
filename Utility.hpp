#ifndef Utility_H
#define Utility_H

#include <SDKDDKVer.h>
#include <boost/asio.hpp>
#include <string>
#include <vector>

class Utility
{
public:
	Utility() = delete;
	~Utility() = delete;
	Utility(const Utility&) = delete;
	Utility(Utility&&) = delete;
	Utility operator=(const Utility&) = delete;
	Utility operator=(Utility&&) = delete;

	static constexpr size_t DEFAULT_TIMEOUT = 500;
	static constexpr size_t MAX_LOGGING_SIZE = 262144;
	static constexpr size_t MAX_PRINTER_SIZE = 256;

	static bool readBytes(boost::asio::io_context&, boost::asio::windows::stream_handle&, void*, size_t&, const size_t);
	static bool readBytes(boost::asio::io_context&, boost::asio::ip::tcp::socket&, void*, size_t&, const size_t);
	static bool writeBytes(boost::asio::io_context&, boost::asio::windows::stream_handle&, const void*, const size_t, const size_t);
	static bool writeBytes(boost::asio::io_context&, boost::asio::ip::tcp::socket&, const void*, const size_t, const size_t);

	static std::string getDateTime();
	static std::vector<std::string> getCOMPorts();
	static std::vector<std::string> getLPTPorts();
	static std::vector<std::string> getUSBDevicePaths();
};

#endif