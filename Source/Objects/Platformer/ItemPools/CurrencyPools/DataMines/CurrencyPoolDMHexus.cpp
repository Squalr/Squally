#include "CurrencyPoolDMHexus.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CurrencyPoolDMHexus::PoolName = "currency-dm-hexus";

CurrencyPoolDMHexus* CurrencyPoolDMHexus::create(ValueMap& properties)
{
	CurrencyPoolDMHexus* instance = new CurrencyPoolDMHexus(properties);

	instance->autorelease();

	return instance;
}

CurrencyPoolDMHexus::CurrencyPoolDMHexus(ValueMap& properties) : super(properties, CurrencyPoolDMHexus::PoolName)
{
	this->addCurrencyToPool(CurrencyPool::CurrencyData((Currency*)IOU::create(), 3 * 3, 3 * 4));
}

CurrencyPoolDMHexus::~CurrencyPoolDMHexus()
{
}
