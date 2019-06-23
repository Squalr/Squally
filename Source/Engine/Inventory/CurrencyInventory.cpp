#include "CurrencyInventory.h"

#include "cocos/base/CCValue.h"

#include "Engine/Save/SaveManager.h"

using namespace cocos2d;

CurrencyInventory::CurrencyInventory(std::string saveKey)
{
	this->currencyMap = ValueMap();
	this->load();
}

CurrencyInventory::~CurrencyInventory()
{
}

void CurrencyInventory::onEnter()
{
	super::onEnter();
}

void CurrencyInventory::initializeListeners()
{
	super::initializeListeners();
}

int CurrencyInventory::getCurrencyCount(std::string currencyKey)
{
	if (this->currencyMap.find(currencyKey) != this->currencyMap.end())
	{
		return this->currencyMap.at(currencyKey).asInt();
	}

	return 0;
}

void CurrencyInventory::removeCurrency(std::string currencyKey, int count)
{
	//TODO
	
	this->save();
}

void CurrencyInventory::addCurrency(std::string currencyKey, int count)
{
	//TODO

	this->save();
}

void CurrencyInventory::save()
{
	if (!this->saveKey.empty())
	{
		SaveManager::saveProfileData(this->saveKey, Value(this->currencyMap));
	}
}

void CurrencyInventory::load()
{
	if (!this->saveKey.empty())
	{
		this->currencyMap = SaveManager::getProfileDataOrDefault(this->saveKey, Value(ValueMap())).asValueMap();
	}
}
