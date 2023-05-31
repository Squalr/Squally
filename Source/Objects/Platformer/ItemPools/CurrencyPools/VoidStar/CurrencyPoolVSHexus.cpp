#include "CurrencyPoolVSHexus.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CurrencyPoolVSHexus::PoolName = "currency-vs-hexus";

CurrencyPoolVSHexus* CurrencyPoolVSHexus::create(ValueMap& properties)
{
	CurrencyPoolVSHexus* instance = new CurrencyPoolVSHexus(properties);

	instance->autorelease();

	return instance;
}

CurrencyPoolVSHexus::CurrencyPoolVSHexus(ValueMap& properties) : super(properties, CurrencyPoolVSHexus::PoolName)
{
	this->addCurrencyToPool(CurrencyPool::CurrencyData((Currency*)IOU::create(), 8 * 3, 8 * 4));
}

CurrencyPoolVSHexus::~CurrencyPoolVSHexus()
{
}
