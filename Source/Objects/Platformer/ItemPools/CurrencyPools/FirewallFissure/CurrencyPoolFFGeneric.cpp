#include "CurrencyPoolFFGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CurrencyPoolFFGeneric::PoolName = "currency-ff-generic";

CurrencyPoolFFGeneric* CurrencyPoolFFGeneric::create(ValueMap& properties)
{
	CurrencyPoolFFGeneric* instance = new CurrencyPoolFFGeneric(properties);

	instance->autorelease();

	return instance;
}

CurrencyPoolFFGeneric::CurrencyPoolFFGeneric(ValueMap& properties) : super(properties, CurrencyPoolFFGeneric::PoolName)
{
	this->addCurrencyToPool(CurrencyPool::CurrencyData((Currency*)IOU::create(), 6 * 2, 6 * 4));
}

CurrencyPoolFFGeneric::~CurrencyPoolFFGeneric()
{
}
