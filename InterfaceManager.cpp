#include "InterfaceManager.hpp"
#include <algorithm>

InterfaceManager::InterfaceManager() : COMHandle(nullptr), LANHandle(nullptr), LPTHandle(nullptr), USBHandle(nullptr), PrinterType()
{
}

InterfaceManager::~InterfaceManager()
{
	this->closeInterfaces();
	PrinterType.clear();
}

COMInterface* InterfaceManager::getCOMInterface() const
{
	return this->COMHandle.get();
}

LANInterface* InterfaceManager::getLANInterface() const
{
	return this->LANHandle.get();
}

LPTInterface* InterfaceManager::getLPTInterface() const
{
	return this->LPTHandle.get();
}

USBInterface* InterfaceManager::getUSBInterface() const
{
	return this->USBHandle.get();
}

bool InterfaceManager::setCOMInterface(const std::string &port)
{
	if (this->COMHandle.get() != nullptr)
	{
		if (!this->COMHandle->closePort())
		{
			this->COMHandle.reset();
			return false;
		}

		this->COMHandle.reset();
	}

	this->COMHandle = std::shared_ptr<COMInterface>(new COMInterface());

	if (this->COMHandle.get() == nullptr)
	{
		return false;
	}

	else if (!this->COMHandle->setPort(port))
	{
		this->COMHandle.reset();
		return false;
	}

	return true;
}

bool InterfaceManager::setLANInterface(const std::string &address, const uint16_t port)
{
	if (this->LANHandle.get() != nullptr)
	{
		if (!this->LANHandle->closePort())
		{
			this->LANHandle.reset();
			return false;
		}

		this->LANHandle.reset();
	}

	this->LANHandle = std::shared_ptr<LANInterface>(new LANInterface());

	if (this->LANHandle.get() == nullptr)
	{
		return false;
	}

	else if (!this->LANHandle->setAddress(address) || !this->LANHandle->setPort(port))
	{
		this->LANHandle.reset();
		return false;
	}

	return true;
}

bool InterfaceManager::setLPTInterface(const std::string &port)
{
	if (this->LPTHandle.get() != nullptr)
	{
		if (!this->LPTHandle->closePort())
		{
			this->LPTHandle.reset();
			return false;
		}

		this->LPTHandle.reset();
	}

	this->LPTHandle = std::shared_ptr<LPTInterface>(new LPTInterface());

	if (this->LPTHandle.get() == nullptr)
	{
		return false;
	}

	else if (!this->LPTHandle->setPort(port))
	{
		this->LPTHandle.reset();
		return false;
	}

	return true;
}

bool InterfaceManager::setUSBInterface(const std::string &devicePath)
{
	if (this->USBHandle.get() != nullptr)
	{
		if (!this->USBHandle->closePort())
		{
			this->USBHandle.reset();
			return false;
		}

		this->USBHandle.reset();
	}

	this->USBHandle = std::shared_ptr<USBInterface>(new USBInterface());

	if (this->USBHandle.get() == nullptr)
	{
		return false;
	}

	else if (!this->USBHandle->setDevicePath(devicePath))
	{
		this->USBHandle.reset();
		return false;
	}

	return true;
}

std::string InterfaceManager::getPrinterType() const
{
	return this->PrinterType;
}

bool InterfaceManager::setPrinterType(const std::string& printerType)
{
	static const std::string labelWord("LABEL"), posWord("POS");
	std::string type(printerType.size(), '\0');

	std::transform(printerType.begin(), printerType.end(), type.begin(), ::toupper);

	if (type != labelWord && type != posWord)
	{
		return false;
	}

	this->PrinterType = type;
	return true;
}

bool InterfaceManager::closeInterfaces()
{
	bool result = true;

	if (this->COMHandle.get() != nullptr)
	{
		if (!this->COMHandle->closePort())
		{
			result = false;
		}

		this->COMHandle.reset();
	}

	if (this->LANHandle.get() != nullptr)
	{
		if (!this->LANHandle->closePort())
		{
			result = false;
		}

		this->LANHandle.reset();
	}

	if (this->LPTHandle.get() != nullptr)
	{
		if (!this->LPTHandle->closePort())
		{
			result = false;
		}

		this->LPTHandle.reset();
	}

	if (this->USBHandle.get() != nullptr)
	{
		if (!this->USBHandle->closePort())
		{
			result = false;
		}

		this->USBHandle.reset();
	}

	return result;
}