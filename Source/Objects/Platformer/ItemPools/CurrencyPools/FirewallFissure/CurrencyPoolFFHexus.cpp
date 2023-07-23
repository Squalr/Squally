#include "CurrencyPoolFFHexus.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string CurrencyPoolFFHexus::PoolName = "currency-ff-generic";

CurrencyPoolFFHexus* CurrencyPoolFFHexus::create(ValueMap& properties)
{
	CurrencyPoolFFHexus* instance = new CurrencyPoolFFHexus(properties);

	instance->autorelease();

	return instance;
}

CurrencyPoolFFHexus::CurrencyPoolFFHexus(ValueMap& properties) : super(properties, CurrencyPoolFFHexus::PoolName)
{
	this->addCurrencyToPool(CurrencyPool::CurrencyData((Currency*)IOU::create(), 6 * 3, 6 * 4));
}

CurrencyPoolFFHexus::~CurrencyPoolFFHexus()
{
}
