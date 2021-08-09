#ifndef InterfaceManager_H
#define InterfaceManager_H

#include <SDKDDKVer.h>
#include "COMInterface.hpp"
#include "LANInterface.hpp"
#include "LPTInterface.hpp"
#include "USBInterface.hpp"
#include <memory>

class InterfaceManager
{
private:
	std::shared_ptr<COMInterface> COMHandle;
	std::shared_ptr<LANInterface> LANHandle;
	std::shared_ptr<LPTInterface> LPTHandle;
	std::shared_ptr<USBInterface> USBHandle;
	std::string PrinterType;

public:
	InterfaceManager();
	~InterfaceManager();
	InterfaceManager(const InterfaceManager&) = delete;
	InterfaceManager(InterfaceManager&&) = delete;
	InterfaceManager& operator=(const InterfaceManager&) = delete;
	InterfaceManager& operator=(InterfaceManager&&) = delete;

	COMInterface* getCOMInterface() const;
	LANInterface* getLANInterface() const;
	LPTInterface* getLPTInterface() const;
	USBInterface* getUSBInterface() const;

	bool setCOMInterface(const std::string&);
	bool setLANInterface(const std::string&, const uint16_t = 65535);
	bool setLPTInterface(const std::string&);
	bool setUSBInterface(const std::string&);

	std::string getPrinterType() const;
	bool setPrinterType(const std::string&);

	bool closeInterfaces();
};

#endif