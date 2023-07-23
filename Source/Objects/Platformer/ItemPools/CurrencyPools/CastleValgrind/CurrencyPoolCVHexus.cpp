#include "CurrencyPoolCVHexus.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CurrencyPoolCVHexus::PoolName = "currency-cv-hexus";

CurrencyPoolCVHexus* CurrencyPoolCVHexus::create(ValueMap& properties)
{
	CurrencyPoolCVHexus* instance = new CurrencyPoolCVHexus(properties);

	instance->autorelease();

	return instance;
}

CurrencyPoolCVHexus::CurrencyPoolCVHexus(ValueMap& properties) : super(properties, CurrencyPoolCVHexus::PoolName)
{
	this->addCurrencyToPool(CurrencyPool::CurrencyData((Currency*)IOU::create(), 4 * 3, 4 * 4));
}

CurrencyPoolCVHexus::~CurrencyPoolCVHexus()
{
}
