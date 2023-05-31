#include "CurrencyPoolURHexus.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CurrencyPoolURHexus::PoolName = "currency-ur-hexus";

CurrencyPoolURHexus* CurrencyPoolURHexus::create(ValueMap& properties)
{
	CurrencyPoolURHexus* instance = new CurrencyPoolURHexus(properties);

	instance->autorelease();

	return instance;
}

CurrencyPoolURHexus::CurrencyPoolURHexus(ValueMap& properties) : super(properties, CurrencyPoolURHexus::PoolName)
{
	this->addCurrencyToPool(CurrencyPool::CurrencyData((Currency*)IOU::create(), 2 * 3, 2 * 4));
}

CurrencyPoolURHexus::~CurrencyPoolURHexus()
{
}
