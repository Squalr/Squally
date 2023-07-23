#include "CurrencyPoolEFHexus.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CurrencyPoolEFHexus::PoolName = "currency-ef-hexus";

CurrencyPoolEFHexus* CurrencyPoolEFHexus::create(ValueMap& properties)
{
	CurrencyPoolEFHexus* instance = new CurrencyPoolEFHexus(properties);

	instance->autorelease();

	return instance;
}

CurrencyPoolEFHexus::CurrencyPoolEFHexus(ValueMap& properties) : super(properties, CurrencyPoolEFHexus::PoolName)
{
	this->addCurrencyToPool(CurrencyPool::CurrencyData((Currency*)IOU::create(), 1 * 3, 1 * 4));
}

CurrencyPoolEFHexus::~CurrencyPoolEFHexus()
{
}
