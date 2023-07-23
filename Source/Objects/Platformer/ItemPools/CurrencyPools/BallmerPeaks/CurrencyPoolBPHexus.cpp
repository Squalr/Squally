#include "CurrencyPoolBPHexus.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CurrencyPoolBPHexus::PoolName = "currency-bp-hexus";

CurrencyPoolBPHexus* CurrencyPoolBPHexus::create(ValueMap& properties)
{
	CurrencyPoolBPHexus* instance = new CurrencyPoolBPHexus(properties);

	instance->autorelease();

	return instance;
}

CurrencyPoolBPHexus::CurrencyPoolBPHexus(ValueMap& properties) : super(properties, CurrencyPoolBPHexus::PoolName)
{
	this->addCurrencyToPool(CurrencyPool::CurrencyData((Currency*)IOU::create(), 7 * 3, 7 * 4));
}

CurrencyPoolBPHexus::~CurrencyPoolBPHexus()
{
}
