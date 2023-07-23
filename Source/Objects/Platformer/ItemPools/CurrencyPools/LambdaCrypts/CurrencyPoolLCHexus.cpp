#include "CurrencyPoolLCHexus.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CurrencyPoolLCHexus::PoolName = "currency-lc-hexus";

CurrencyPoolLCHexus* CurrencyPoolLCHexus::create(ValueMap& properties)
{
	CurrencyPoolLCHexus* instance = new CurrencyPoolLCHexus(properties);

	instance->autorelease();

	return instance;
}

CurrencyPoolLCHexus::CurrencyPoolLCHexus(ValueMap& properties) : super(properties, CurrencyPoolLCHexus::PoolName)
{
	this->addCurrencyToPool(CurrencyPool::CurrencyData((Currency*)IOU::create(), 6 * 3, 6 * 4));
}

CurrencyPoolLCHexus::~CurrencyPoolLCHexus()
{
}
