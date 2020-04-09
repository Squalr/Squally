#include "CurrencyPoolEFGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CurrencyPoolEFGeneric::PoolName = "currency-ef-generic";

CurrencyPoolEFGeneric* CurrencyPoolEFGeneric::create(ValueMap& properties)
{
	CurrencyPoolEFGeneric* instance = new CurrencyPoolEFGeneric(properties);

	instance->autorelease();

	return instance;
}

CurrencyPoolEFGeneric::CurrencyPoolEFGeneric(ValueMap& properties) : super(properties, CurrencyPoolEFGeneric::PoolName)
{
	this->addCurrencyToPool(CurrencyPool::CurrencyData((Currency*)IOU::create(), 2, 4));
}

CurrencyPoolEFGeneric::~CurrencyPoolEFGeneric()
{
}
