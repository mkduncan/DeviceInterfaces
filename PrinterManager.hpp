#ifndef PrinterManager_H
#define PrinterManager_H

#include <SDKDDKVer.h>
#include "InterfaceManager.hpp"

class PrinterManager
{
private:
	static std::vector<std::shared_ptr<InterfaceManager>> Printers;
	static size_t Index;

public:
	PrinterManager() = delete;
	~PrinterManager() = delete;
	PrinterManager(const PrinterManager&) = delete;
	PrinterManager(PrinterManager&&) = delete;
	PrinterManager& operator=(const PrinterManager&) = delete;
	PrinterManager& operator=(PrinterManager&&) = delete;

	static bool addPrinters(const size_t = 1);
	static bool clearPrinters();
	static size_t getPrinterCount();
	static size_t getSelectionIndex();
	static InterfaceManager* getSelection();
	static bool selectPrinterIndex(const size_t);

	static bool setCOMBaudRate(const uint32_t);
	static bool setCOMByteSize(const uint8_t);
	static bool setCOMParity(const uint8_t);
	static bool setCOMPort(const std::string&);
	static bool setCOMStopBits(const uint8_t);
	static bool setCOMTimeout(const size_t);
	static uint32_t getCOMBaudRate();
	static bool getCOMIsBluetooth();
	static uint8_t getCOMByteSize();
	static uint8_t getCOMParity();
	static std::string getCOMPort();
	static uint8_t getCOMStopBits();
	static size_t getCOMTimeout();

	static bool setLANAddress(const std::string&);
	static bool setLANPort(const uint16_t);
	static bool setLANTimeout(const size_t);
	static std::string getLANAddress();
	static uint16_t getLANPort();
	static size_t getLANTimeout();

	static bool setLPTPort(const std::string&);
	static bool setLPTTimeout(const size_t);
	static std::string getLPTPort();
	static size_t getLPTTimeout();

	static bool setUSBDevicePath(const std::string&);
	static bool setUSBTimeout(const size_t);
	static std::string getUSBDevicePath();
	static size_t getUSBTimeout();

	static std::string getPrinterType();
	static bool setPrinterType(const std::string&);

	static bool openCOMPort();
	static bool readCOMData(std::string&, const size_t);
	static bool readCOMData(std::vector<uint8_t>&, const size_t);
	static bool writeCOMData(const std::string&);
	static bool writeCOMData(const std::vector<uint8_t>&);
	static bool closeCOMPort();

	static bool openLANPort();
	static bool readLANData(std::string&, const size_t);
	static bool readLANData(std::vector<uint8_t>&, const size_t);
	static bool writeLANData(const std::string&);
	static bool writeLANData(const std::vector<uint8_t>&);
	static bool closeLANPort();

	static bool openLPTPort();
	static bool readLPTData(std::string&, const size_t);
	static bool readLPTData(std::vector<uint8_t>&, const size_t);
	static bool writeLPTData(const std::string&);
	static bool writeLPTData(const std::vector<uint8_t>&);
	static bool closeLPTPort();

	static bool openUSBPort();
	static bool readUSBData(std::string&, const size_t);
	static bool readUSBData(std::vector<uint8_t>&, const size_t);
	static bool writeUSBData(const std::string&);
	static bool writeUSBData(const std::vector<uint8_t>&);
	static bool closeUSBPort();
};

#endif