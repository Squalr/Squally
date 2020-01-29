#include "CurrencyPoolEFGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"
#include "Objects/Platformer/Collectables/IOU.h"

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
	this->addCurrencyToPool(CurrencyPool::Currency(IOU::getIdentifier(), 2, 4));
}

CurrencyPoolEFGeneric::~CurrencyPoolEFGeneric()
{
}
