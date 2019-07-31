#include "CurrencyInventory.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/InventoryEvents.h"
#include "Engine/Save/SaveManager.h"

using namespace cocos2d;

CurrencyInventory* CurrencyInventory::create(std::string saveKey)
{
	CurrencyInventory* instance = new CurrencyInventory(saveKey);

	instance->autorelease();

	return instance;
}

CurrencyInventory::CurrencyInventory(std::string saveKey)
{
	this->saveKey = saveKey;
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

	this->addEventListenerIgnorePause(EventListenerCustom::create(InventoryEvents::EventCurrencyInventoryInstanceChangedPrefix + this->saveKey, [=](EventCustom* eventCustom)
	{
		InventoryEvents::CurrencyInventoryInstanceChangedArgs* args = static_cast<InventoryEvents::CurrencyInventoryInstanceChangedArgs*>(eventCustom->getUserData());
		
		if (args != nullptr && args->instance != this)
		{
			this->load();
		}
	}));
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
	if (this->currencyMap.find(currencyKey) != this->currencyMap.end())
	{
		this->currencyMap[currencyKey] = Value(this->currencyMap.at(currencyKey).asInt() - count);
	}
	else
	{
		this->currencyMap[currencyKey] = Value(0);
	}

	this->save();
}

void CurrencyInventory::addCurrency(std::string currencyKey, int count)
{
	if (this->currencyMap.find(currencyKey) != this->currencyMap.end())
	{
		this->currencyMap[currencyKey] = Value(this->currencyMap.at(currencyKey).asInt() + count);
	}
	else
	{
		this->currencyMap[currencyKey] = Value(count);
	}
	
	this->save();
}

void CurrencyInventory::save()
{
	if (!this->saveKey.empty())
	{
		SaveManager::saveProfileData(this->saveKey, Value(this->currencyMap));
		
		InventoryEvents::TriggerCurrencyInventoryInstanceChanged(InventoryEvents::CurrencyInventoryInstanceChangedArgs(this, this->saveKey));
	}
}

void CurrencyInventory::load()
{
	if (!this->saveKey.empty())
	{
		this->currencyMap = SaveManager::getProfileDataOrDefault(this->saveKey, Value(ValueMap())).asValueMap();
	}
}
