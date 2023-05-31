#include "CurrencyPoolLCGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CurrencyPoolLCGeneric::PoolName = "currency-lc-generic";

CurrencyPoolLCGeneric* CurrencyPoolLCGeneric::create(ValueMap& properties)
{
	CurrencyPoolLCGeneric* instance = new CurrencyPoolLCGeneric(properties);

	instance->autorelease();

	return instance;
}

CurrencyPoolLCGeneric::CurrencyPoolLCGeneric(ValueMap& properties) : super(properties, CurrencyPoolLCGeneric::PoolName)
{
	this->addCurrencyToPool(CurrencyPool::CurrencyData((Currency*)IOU::create(), 5 * 2, 5 * 4));
}

CurrencyPoolLCGeneric::~CurrencyPoolLCGeneric()
{
}
