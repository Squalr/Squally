#include "CurrencyPoolURGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CurrencyPoolURGeneric::PoolName = "currency-ur-generic";

CurrencyPoolURGeneric* CurrencyPoolURGeneric::create(ValueMap& properties)
{
	CurrencyPoolURGeneric* instance = new CurrencyPoolURGeneric(properties);

	instance->autorelease();

	return instance;
}

CurrencyPoolURGeneric::CurrencyPoolURGeneric(ValueMap& properties) : super(properties, CurrencyPoolURGeneric::PoolName)
{
	this->addCurrencyToPool(CurrencyPool::CurrencyData((Currency*)IOU::create(), 3, 5));
}

CurrencyPoolURGeneric::~CurrencyPoolURGeneric()
{
}
