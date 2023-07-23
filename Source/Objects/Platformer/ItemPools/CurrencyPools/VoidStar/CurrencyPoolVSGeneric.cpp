#include "CurrencyPoolVSGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CurrencyPoolVSGeneric::PoolName = "currency-vs-generic";

CurrencyPoolVSGeneric* CurrencyPoolVSGeneric::create(ValueMap& properties)
{
	CurrencyPoolVSGeneric* instance = new CurrencyPoolVSGeneric(properties);

	instance->autorelease();

	return instance;
}

CurrencyPoolVSGeneric::CurrencyPoolVSGeneric(ValueMap& properties) : super(properties, CurrencyPoolVSGeneric::PoolName)
{
	this->addCurrencyToPool(CurrencyPool::CurrencyData((Currency*)IOU::create(), 8 * 2, 8 * 4));
}

CurrencyPoolVSGeneric::~CurrencyPoolVSGeneric()
{
}
