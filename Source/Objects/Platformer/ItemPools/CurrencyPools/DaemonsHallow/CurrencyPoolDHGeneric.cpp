#include "CurrencyPoolDHGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CurrencyPoolDHGeneric::PoolName = "currency-dh-generic";

CurrencyPoolDHGeneric* CurrencyPoolDHGeneric::create(ValueMap& properties)
{
	CurrencyPoolDHGeneric* instance = new CurrencyPoolDHGeneric(properties);

	instance->autorelease();

	return instance;
}

CurrencyPoolDHGeneric::CurrencyPoolDHGeneric(ValueMap& properties) : super(properties, CurrencyPoolDHGeneric::PoolName)
{
	this->addCurrencyToPool(CurrencyPool::CurrencyData((Currency*)IOU::create(), 6, 9));
}

CurrencyPoolDHGeneric::~CurrencyPoolDHGeneric()
{
}
