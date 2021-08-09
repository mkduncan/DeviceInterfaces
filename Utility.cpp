#include "Utility.hpp"
#include "Logger.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/optional.hpp>
#include <boost/format.hpp>
#include <initguid.h>
#include <setupapi.h>

bool Utility::readBytes(boost::asio::io_context& context, boost::asio::windows::stream_handle& stream, void* data, size_t& bytes, const size_t timeout)
{
	try
	{
		boost::optional<boost::system::error_code> timerResult, readResult;
		boost::asio::deadline_timer timer(context);

		if (!stream.is_open())
		{
			Logger::addErrorLog(__LINE__, std::string("Utility::readBytes()"), std::string("Failed to read bytes due to closed asychronous stream handle."));
			return false;
		}

		timer.expires_from_now(boost::posix_time::milliseconds(timeout));
		timer.async_wait([&timerResult](const boost::system::error_code& error) { timerResult.reset(error); });
		boost::asio::async_read(stream, boost::asio::buffer(data, bytes), [&readResult, &bytes](const boost::system::error_code& error, size_t bytesRead) { readResult.reset(error); bytes = bytesRead; });
		context.reset();

		while (context.run_one())
		{
			if (readResult)
				timer.cancel();

			else if (timerResult)
				stream.cancel();
		}

		if (*readResult)
			return false;
	}

	catch (const boost::system::system_error& exception)
	{
		Logger::addErrorLog(__LINE__, std::string("Utility::readBytes()"), std::string("Failed to read bytes from asychronous stream handle."));
		Logger::addErrorLog(__LINE__, std::string("Utility::readBytes()"), std::string("System reported error code = ") + std::to_string(exception.code().value()));

		return false;
	}

	return true;
}

bool Utility::readBytes(boost::asio::io_context& context, boost::asio::ip::tcp::socket& socket, void* data, size_t& bytes, const size_t timeout)
{
	try
	{
		boost::optional<boost::system::error_code> timerResult, readResult;
		boost::asio::deadline_timer timer(context);

		if (!socket.is_open())
		{
			Logger::addErrorLog(__LINE__, std::string("Utility::readBytes()"), std::string("Failed to read bytes due to closed asychronous stream handle."));
			return false;
		}

		timer.expires_from_now(boost::posix_time::milliseconds(timeout));
		timer.async_wait([&timerResult](const boost::system::error_code& error) { timerResult.reset(error); });
		boost::asio::async_read(socket, boost::asio::buffer(data, bytes), [&readResult, &bytes](const boost::system::error_code& error, size_t bytesRead) { readResult.reset(error); bytes = bytesRead; });
		context.reset();

		while (context.run_one())
		{
			if (readResult)
				timer.cancel();

			else if (timerResult)
				socket.cancel();
		}

		if (*readResult)
			return false;
	}

	catch (const boost::system::system_error& exception)
	{
		Logger::addErrorLog(__LINE__, std::string("Utility::readBytes()"), std::string("Failed to read bytes from asychronous stream handle."));
		Logger::addErrorLog(__LINE__, std::string("Utility::readBytes()"), std::string("System reported error code = ") + std::to_string(exception.code().value()));

		return false;
	}

	return true;
}

bool Utility::writeBytes(boost::asio::io_context& context, boost::asio::windows::stream_handle& stream, const void* data, const size_t bytes, const size_t timeout)
{
	try
	{
		boost::optional<boost::system::error_code> timerResult, writeResult;
		boost::asio::deadline_timer timer(context);

		if (!stream.is_open())
		{
			Logger::addErrorLog(__LINE__, std::string("Utility::writeBytes()"), std::string("Failed to write bytes due to closed asychronous stream handle."));
			return false;
		}

		timer.expires_from_now(boost::posix_time::milliseconds(timeout));
		timer.async_wait([&timerResult](const boost::system::error_code& error) { timerResult.reset(error); });
		boost::asio::async_write(stream, boost::asio::buffer(data, bytes), [&writeResult](const boost::system::error_code& error, size_t) { writeResult.reset(error); });
		context.reset();

		while (context.run_one())
		{
			if (writeResult)
				timer.cancel();

			else if (timerResult)
				stream.cancel();
		}

		if (*writeResult)
			return false;
	}

	catch (const boost::system::system_error& exception)
	{
		Logger::addErrorLog(__LINE__, std::string("Utility::writeBytes()"), std::string("Failed to write bytes to asychronous stream handle."));
		Logger::addErrorLog(__LINE__, std::string("Utility::writeBytes()"), std::string("System reported error code = ") + std::to_string(exception.code().value()));

		return false;
	}

	return true;
}

bool Utility::writeBytes(boost::asio::io_context& context, boost::asio::ip::tcp::socket& socket, const void* data, const size_t bytes, const size_t timeout)
{
	try
	{
		boost::optional<boost::system::error_code> timerResult, writeResult;
		boost::asio::deadline_timer timer(context);

		if (!socket.is_open())
		{
			Logger::addErrorLog(__LINE__, std::string("Utility::writeBytes()"), std::string("Failed to write bytes due to closed asychronous stream handle."));
			return false;
		}

		timer.expires_from_now(boost::posix_time::milliseconds(timeout));
		timer.async_wait([&timerResult](const boost::system::error_code& error) { timerResult.reset(error); });
		boost::asio::async_write(socket, boost::asio::buffer(data, bytes), [&writeResult](const boost::system::error_code& error, size_t) { writeResult.reset(error); });
		context.reset();

		while (context.run_one())
		{
			if (writeResult)
				timer.cancel();

			else if (timerResult)
				socket.cancel();
		}

		if (*writeResult)
			return false;
	}

	catch (const boost::system::system_error& exception)
	{
		Logger::addErrorLog(__LINE__, std::string("Utility::writeBytes()"), std::string("Failed to write bytes to asychronous stream handle."));
		Logger::addErrorLog(__LINE__, std::string("Utility::writeBytes()"), std::string("System reported error code = ") + std::to_string(exception.code().value()));

		return false;
	}

	return true;
}

std::string Utility::getDateTime()
{
	static const std::string format("%02d/%02d/%s %02d:%02d");

	try
	{
		const boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
		const boost::format output = boost::format(format) % now.date().year_month_day().month.as_number() % now.date().year_month_day().day.as_number() % now.date().year_month_day().year % now.time_of_day().hours() % now.time_of_day().minutes();

		return output.str();
	}

	catch (...)
	{
		return std::string();
	}

	return std::string();
}

std::vector<std::string> Utility::getCOMPorts()
{
	static const std::string portType("COM");
	std::vector<std::string> result;
	std::string buffer(0x3FFF, '\0'), portName;

	for (uint16_t index = 0; index < 256; ++index)
	{
		portName = portType + std::to_string(index);

		if (::QueryDosDevice(portName.c_str(), &buffer[0], static_cast<DWORD>(buffer.size())) != 0)
			result.push_back(portName);
	}

	return result;
}

std::vector<std::string> Utility::getLPTPorts()
{
	static const std::string portType("LPT");
	std::vector<std::string> result;
	std::string buffer(0x3FFF, '\0'), portName;

	for (uint16_t index = 0; index < 256; ++index)
	{
		portName = portType + std::to_string(index);

		if (::QueryDosDevice(portName.c_str(), &buffer[0], static_cast<DWORD>(buffer.size())) != 0)
			result.push_back(portName);
	}

	return result;
}

DEFINE_GUID(GUID_CLASS_TPG_BULK, 0xc12127c7, 0x8258, 0x4929, 0x85, 0x74, 0x42, 0x78, 0xb9, 0x46, 0xcd, 0x69);
DEFINE_GUID(GUID_CLASS_PTR_BULK, 0x28d78fad, 0x5a12, 0x11D1, 0xae, 0x5b, 0x00, 0x00, 0xf8, 0x03, 0xa8, 0xc2);

std::vector<std::string> Utility::getUSBDevicePaths()
{
	static const LPGUID lNativeClassGUID = (LPGUID)& GUID_CLASS_TPG_BULK, lPrinterClassGUID = (LPGUID)& GUID_CLASS_PTR_BULK;
	static const std::vector<uint16_t> usbVIDList({ 0x05D9, 0x0AA7, 0x03F0, 0x1840 }), usbPIDList({ 0x1002, 0xC760, 0xC776, 0xC795, 0xC798, 0xC799, 0x0760, 0x0776, 0x0795, 0xA760, 0xA776, 0xA795, 0x0300, 0x0301, 0x0302, 0x0303, 0x0306, 0x0307, 0x0308, 0x0309, 0x030F, 0x0310, 0x0311, 0x0312, 0x1E24, 0x3024, 0x3624, 0x0257, 0x0F56, 0x0357, 0x0157, 0x0100 });
	static const std::string hexFormat("%04x"), vidPrefix("VID_"), pidPrefix("&PID_");
	std::vector<std::string> results;

	try
	{
		for (uint8_t iInterfaceId = 0; iInterfaceId <= 1; ++iInterfaceId)
		{
			SP_INTERFACE_DEVICE_DATA sDeviceInterfaceData;
			PSP_INTERFACE_DEVICE_DETAIL_DATA pFunctionClassDeviceData = nullptr;
			LPGUID lGUID = nullptr;
			HGLOBAL hMemory = nullptr;
			HDEVINFO hDeviceHandleInfo = INVALID_HANDLE_VALUE;
			HANDLE hOutput = INVALID_HANDLE_VALUE;
			DWORD uIndex = 0;
			ULONG uPredictedLength = 0, uRequiredLength = 0;
			std::string sDevicePath, vidName, pidName;

			if (iInterfaceId == 0)
				lGUID = lNativeClassGUID;

			else
				lGUID = lPrinterClassGUID;

			hDeviceHandleInfo = ::SetupDiGetClassDevs(lGUID, nullptr, nullptr, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);

			if (hDeviceHandleInfo == INVALID_HANDLE_VALUE)
				return results;

			sDeviceInterfaceData.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);

			while (::SetupDiEnumDeviceInterfaces(hDeviceHandleInfo, nullptr, lGUID, uIndex, &sDeviceInterfaceData))
			{
				::SetupDiGetInterfaceDeviceDetail(hDeviceHandleInfo, &sDeviceInterfaceData, nullptr, 0, &uRequiredLength, nullptr);

				uPredictedLength = uRequiredLength;
				hMemory = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, static_cast<DWORD>(uPredictedLength));

				if (hMemory == nullptr)
				{
					::SetupDiDestroyDeviceInfoList(hDeviceHandleInfo);
					return results;
				}

				pFunctionClassDeviceData = (PSP_INTERFACE_DEVICE_DETAIL_DATA)::GlobalLock(hMemory);

				if (pFunctionClassDeviceData == nullptr)
				{
					::GlobalFree(hMemory);
					::SetupDiDestroyDeviceInfoList(hDeviceHandleInfo);

					return results;
				}

				pFunctionClassDeviceData->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);

				if (!::SetupDiGetInterfaceDeviceDetail(hDeviceHandleInfo, &sDeviceInterfaceData, pFunctionClassDeviceData, uPredictedLength, &uRequiredLength, nullptr))
				{
					::GlobalUnlock(hMemory);
					::GlobalFree(hMemory);
					::SetupDiDestroyDeviceInfoList(hDeviceHandleInfo);

					return results;
				}

				hOutput = ::CreateFile(pFunctionClassDeviceData->DevicePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);

				if (hOutput != INVALID_HANDLE_VALUE)
				{
					sDevicePath = std::string(pFunctionClassDeviceData->DevicePath);
					std::transform(sDevicePath.begin(), sDevicePath.end(), sDevicePath.begin(), ::toupper);

					for (size_t iVID = 0; iVID < usbVIDList.size(); ++iVID)
					{
						vidName = (boost::format(vidPrefix + hexFormat) % usbVIDList[iVID]).str();
						boost::to_upper(vidName);

						for (size_t iPID = 0; iPID < usbPIDList.size(); ++iPID)
						{
							pidName = (boost::format(pidPrefix + hexFormat) % usbPIDList[iPID]).str();
							boost::to_upper(pidName);

							if (sDevicePath.find(vidName + pidName) != std::string::npos)
							{
								results.push_back(sDevicePath);
								break;
							}
						}
					}

					::CloseHandle(hOutput);
				}

				::GlobalUnlock(hMemory);
				::GlobalFree(hMemory);

				++uIndex;
			}

			if (!::SetupDiDestroyDeviceInfoList(hDeviceHandleInfo))
				return results;
		}

		return results;
	}

	catch (...)
	{
		return results;
	}

	return results;
}