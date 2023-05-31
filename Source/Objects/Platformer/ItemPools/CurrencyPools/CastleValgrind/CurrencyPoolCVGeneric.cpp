#include "CurrencyPoolCVGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CurrencyPoolCVGeneric::PoolName = "currency-cv-generic";

CurrencyPoolCVGeneric* CurrencyPoolCVGeneric::create(ValueMap& properties)
{
	CurrencyPoolCVGeneric* instance = new CurrencyPoolCVGeneric(properties);

	instance->autorelease();

	return instance;
}

CurrencyPoolCVGeneric::CurrencyPoolCVGeneric(ValueMap& properties) : super(properties, CurrencyPoolCVGeneric::PoolName)
{
	this->addCurrencyToPool(CurrencyPool::CurrencyData((Currency*)IOU::create(), 4 * 2, 4 * 4));
}

CurrencyPoolCVGeneric::~CurrencyPoolCVGeneric()
{
}
