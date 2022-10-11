#include "CurrencyPoolDMGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CurrencyPoolDMGeneric::PoolName = "currency-dm-generic";

CurrencyPoolDMGeneric* CurrencyPoolDMGeneric::create(ValueMap& properties)
{
	CurrencyPoolDMGeneric* instance = new CurrencyPoolDMGeneric(properties);

	instance->autorelease();

	return instance;
}

CurrencyPoolDMGeneric::CurrencyPoolDMGeneric(ValueMap& properties) : super(properties, CurrencyPoolDMGeneric::PoolName)
{
	this->addCurrencyToPool(CurrencyPool::CurrencyData((Currency*)IOU::create(), 3, 5));
}

CurrencyPoolDMGeneric::~CurrencyPoolDMGeneric()
{
}
