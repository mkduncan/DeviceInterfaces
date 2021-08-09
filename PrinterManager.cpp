#include "PrinterManager.hpp"
#include "Utility.hpp"

std::vector<std::shared_ptr<InterfaceManager>> PrinterManager::Printers;
size_t PrinterManager::Index = 0;

bool PrinterManager::addPrinters(const size_t count)
{
	size_t oldCount = PrinterManager::Printers.size();

	if (count == 0 || count + oldCount > Utility::MAX_PRINTER_SIZE)
	{
		return false;
	}

	for (size_t index = 0; index < count; ++index)
	{
		PrinterManager::Printers.push_back(std::shared_ptr<InterfaceManager>(new InterfaceManager()));
	}

	return PrinterManager::Printers.size() - oldCount == count;
}

bool PrinterManager::clearPrinters()
{
	bool result = true;

	for (size_t index = 0; index < PrinterManager::Printers.size(); ++index)
	{
		if (!PrinterManager::Printers[index]->closeInterfaces())
		{
			result = false;
		}
	}

	PrinterManager::Printers.clear();
	PrinterManager::Index = 0;

	return result;
}

size_t PrinterManager::getPrinterCount()
{
	return PrinterManager::Printers.size();
}

size_t PrinterManager::getSelectionIndex()
{
	return PrinterManager::Index;
}

InterfaceManager* PrinterManager::getSelection()
{
	if (PrinterManager::Printers.empty())
	{
		return nullptr;
	}

	return PrinterManager::Printers[PrinterManager::Index].get();
}

bool PrinterManager::selectPrinterIndex(const size_t index)
{
	if (index >= PrinterManager::Printers.size())
	{
		return false;
	}

	PrinterManager::Index = index;
	return true;
}

bool PrinterManager::setCOMBaudRate(const uint32_t baudRate)
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getCOMInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getCOMInterface()->setBaudRate(baudRate);
}

bool PrinterManager::setCOMByteSize(const uint8_t byteSize)
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getCOMInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getCOMInterface()->setByteSize(byteSize);
}

bool PrinterManager::setCOMParity(const uint8_t parity)
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getCOMInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getCOMInterface()->setParity(parity);
}

bool PrinterManager::setCOMPort(const std::string& port)
{
	if (PrinterManager::getSelection() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->setCOMInterface(port);
}

bool PrinterManager::setCOMStopBits(const uint8_t stopBits)
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getCOMInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getCOMInterface()->setStopBits(stopBits);
}

bool PrinterManager::setCOMTimeout(const size_t timeout)
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getCOMInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getCOMInterface()->setTimeout(timeout);
}

uint32_t PrinterManager::getCOMBaudRate()
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getCOMInterface() == nullptr)
	{
		return 0;
	}

	return PrinterManager::getSelection()->getCOMInterface()->getBaudRate() ;
}

bool PrinterManager::getCOMIsBluetooth()
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getCOMInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getCOMInterface()->isBluetooth();
}

uint8_t PrinterManager::getCOMByteSize()
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getCOMInterface() == nullptr)
	{
		return 0;
	}

	return PrinterManager::getSelection()->getCOMInterface()->getByteSize();
}

uint8_t PrinterManager::getCOMParity()
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getCOMInterface() == nullptr)
	{
		return 0;
	}

	return PrinterManager::getSelection()->getCOMInterface()->getParity();
}

std::string PrinterManager::getCOMPort()
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getCOMInterface() == nullptr)
	{
		return std::string();
	}

	return PrinterManager::getSelection()->getCOMInterface()->getPort();
}

uint8_t PrinterManager::getCOMStopBits()
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getCOMInterface() == nullptr)
	{
		return 0;
	}

	return PrinterManager::getSelection()->getCOMInterface()->getStopBits();
}

size_t PrinterManager::getCOMTimeout()
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getCOMInterface() == nullptr)
	{
		return 0;
	}

	return PrinterManager::getSelection()->getCOMInterface()->getTimeout();
}

bool PrinterManager::setLANAddress(const std::string& address)
{
	if (PrinterManager::getSelection() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->setLANInterface(address);
}

bool PrinterManager::setLANPort(const uint16_t port)
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getLANInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getLANInterface()->setPort(port);
}

bool PrinterManager::setLANTimeout(const size_t timeout)
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getLANInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getLANInterface()->setTimeout(timeout);
}

std::string PrinterManager::getLANAddress()
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getLANInterface() == nullptr)
	{
		return std::string();
	}

	return PrinterManager::getSelection()->getLANInterface()->getAddress();
}

uint16_t PrinterManager::getLANPort()
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getLANInterface() == nullptr)
	{
		return 0;
	}

	return PrinterManager::getSelection()->getLANInterface()->getPort();
}

size_t PrinterManager::getLANTimeout()
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getLANInterface() == nullptr)
	{
		return 0;
	}

	return PrinterManager::getSelection()->getLANInterface()->getTimeout();
}

bool PrinterManager::setLPTPort(const std::string& port)
{
	if (PrinterManager::getSelection() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->setLPTInterface(port);
}

bool PrinterManager::setLPTTimeout(const size_t timeout)
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getLPTInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getLPTInterface()->setTimeout(timeout);
}

std::string PrinterManager::getLPTPort()
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getLPTInterface() == nullptr)
	{
		return std::string();
	}

	return PrinterManager::getSelection()->getLPTInterface()->getPort();
}

size_t PrinterManager::getLPTTimeout()
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getLPTInterface() == nullptr)
	{
		return 0;
	}

	return PrinterManager::getSelection()->getLPTInterface()->getTimeout();
}

bool PrinterManager::setUSBDevicePath(const std::string& devicePath)
{
	if (PrinterManager::getSelection() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->setUSBInterface(devicePath);
}

bool PrinterManager::setUSBTimeout(const size_t timeout)
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getUSBInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getUSBInterface()->setTimeout(timeout);
}

std::string PrinterManager::getUSBDevicePath()
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getUSBInterface() == nullptr)
	{
		return std::string();
	}

	return PrinterManager::getSelection()->getUSBInterface()->getDevicePath();
}

size_t PrinterManager::getUSBTimeout()
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getUSBInterface() == nullptr)
	{
		return 0;
	}

	return PrinterManager::getSelection()->getUSBInterface()->getTimeout();
}

std::string PrinterManager::getPrinterType()
{
	if (PrinterManager::getSelection() == nullptr)
	{
		return std::string();
	}

	return PrinterManager::getSelection()->getPrinterType();
}

bool PrinterManager::setPrinterType(const std::string &printerType)
{
	if (PrinterManager::getSelection() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->setPrinterType(printerType);
}

bool PrinterManager::openCOMPort()
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getCOMInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getCOMInterface()->openPort();
}

bool PrinterManager::readCOMData(std::string& data, const size_t size)
{
	static const std::string labelWord("LABEL");

	if (PrinterManager::getPrinterType() != labelWord || PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getCOMInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getCOMInterface()->readData(data, size);
}

bool PrinterManager::readCOMData(std::vector<uint8_t>& data, const size_t size)
{
	static const std::string posWord("POS");

	if (PrinterManager::getPrinterType() != posWord || PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getCOMInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getCOMInterface()->readData(data, size);
}

bool PrinterManager::writeCOMData(const std::string& data)
{
	static const std::string labelWord("LABEL");

	if (PrinterManager::getPrinterType() != labelWord || PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getCOMInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getCOMInterface()->writeData(data);
}

bool PrinterManager::writeCOMData(const std::vector<uint8_t>& data)
{
	static const std::string posWord("POS");

	if (PrinterManager::getPrinterType() != posWord || PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getCOMInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getCOMInterface()->writeData(data);
}

bool PrinterManager::closeCOMPort()
{
	if (PrinterManager::getSelection() != nullptr && PrinterManager::getSelection()->getCOMInterface() != nullptr)
	{
		return PrinterManager::getSelection()->getCOMInterface()->closePort();
	}

	return true;
}

bool PrinterManager::openLANPort()
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getLANInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getLANInterface()->openPort();
}

bool PrinterManager::readLANData(std::string& data, const size_t size)
{
	static const std::string labelWord("LABEL");

	if (PrinterManager::getPrinterType() != labelWord || PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getLANInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getLANInterface()->readData(data, size);
}

bool PrinterManager::readLANData(std::vector<uint8_t>& data, const size_t size)
{
	static const std::string posWord("POS");

	if (PrinterManager::getPrinterType() != posWord || PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getLANInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getLANInterface()->readData(data, size);
}

bool PrinterManager::writeLANData(const std::string& data)
{
	static const std::string labelWord("LABEL");

	if (PrinterManager::getPrinterType() != labelWord || PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getLANInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getLANInterface()->writeData(data);
}

bool PrinterManager::writeLANData(const std::vector<uint8_t>& data)
{
	static const std::string posWord("POS");

	if (PrinterManager::getPrinterType() != posWord || PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getLANInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getLANInterface()->writeData(data);
}

bool PrinterManager::closeLANPort()
{
	if (PrinterManager::getSelection() != nullptr && PrinterManager::getSelection()->getLANInterface() != nullptr)
	{
		return PrinterManager::getSelection()->getLANInterface()->closePort();
	}

	return true;
}

bool PrinterManager::openLPTPort()
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getLPTInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getLPTInterface()->openPort();
}

bool PrinterManager::readLPTData(std::string& data, const size_t size)
{
	static const std::string labelWord("LABEL");

	if (PrinterManager::getPrinterType() != labelWord || PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getLPTInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getLPTInterface()->readData(data, size);
}

bool PrinterManager::readLPTData(std::vector<uint8_t>& data, const size_t size)
{
	static const std::string posWord("POS");

	if (PrinterManager::getPrinterType() != posWord || PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getLPTInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getLPTInterface()->readData(data, size);
}

bool PrinterManager::writeLPTData(const std::string& data)
{
	static const std::string labelWord("LABEL");

	if (PrinterManager::getPrinterType() != labelWord || PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getLPTInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getLPTInterface()->writeData(data);
}

bool PrinterManager::writeLPTData(const std::vector<uint8_t>& data)
{
	static const std::string posWord("POS");

	if (PrinterManager::getPrinterType() != posWord || PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getLPTInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getLPTInterface()->writeData(data);
}

bool PrinterManager::closeLPTPort()
{
	if (PrinterManager::getSelection() != nullptr && PrinterManager::getSelection()->getLPTInterface() != nullptr)
	{
		return PrinterManager::getSelection()->getLPTInterface()->closePort();
	}

	return true;
}

bool PrinterManager::openUSBPort()
{
	if (PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getUSBInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getUSBInterface()->openPort();
}

bool PrinterManager::readUSBData(std::string& data, const size_t size)
{
	static const std::string labelWord("LABEL");

	if (PrinterManager::getPrinterType() != labelWord || PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getUSBInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getUSBInterface()->readData(data, size);
}

bool PrinterManager::readUSBData(std::vector<uint8_t>& data, const size_t size)
{
	static const std::string posWord("POS");

	if (PrinterManager::getPrinterType() != posWord || PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getUSBInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getUSBInterface()->readData(data, size);
}

bool PrinterManager::writeUSBData(const std::string& data)
{
	static const std::string labelWord("LABEL");

	if (PrinterManager::getPrinterType() != labelWord || PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getUSBInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getUSBInterface()->writeData(data);
}

bool PrinterManager::writeUSBData(const std::vector<uint8_t>& data)
{
	static const std::string posWord("POS");

	if (PrinterManager::getPrinterType() != posWord || PrinterManager::getSelection() == nullptr || PrinterManager::getSelection()->getUSBInterface() == nullptr)
	{
		return false;
	}

	return PrinterManager::getSelection()->getUSBInterface()->writeData(data);
}

bool PrinterManager::closeUSBPort()
{
	if (PrinterManager::getSelection() != nullptr && PrinterManager::getSelection()->getUSBInterface() != nullptr)
	{
		return PrinterManager::getSelection()->getUSBInterface()->closePort();
	}

	return true;
}