#include "CurrencyPoolBPGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CurrencyPoolBPGeneric::PoolName = "currency-bp-generic";

CurrencyPoolBPGeneric* CurrencyPoolBPGeneric::create(ValueMap& properties)
{
	CurrencyPoolBPGeneric* instance = new CurrencyPoolBPGeneric(properties);

	instance->autorelease();

	return instance;
}

CurrencyPoolBPGeneric::CurrencyPoolBPGeneric(ValueMap& properties) : super(properties, CurrencyPoolBPGeneric::PoolName)
{
	this->addCurrencyToPool(CurrencyPool::CurrencyData((Currency*)IOU::create(), 7, 10));
}

CurrencyPoolBPGeneric::~CurrencyPoolBPGeneric()
{
}
