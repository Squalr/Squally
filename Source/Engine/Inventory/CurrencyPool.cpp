#include "CurrencyPool.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ItemEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/Currency.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

CurrencyPool::CurrencyPool(std::string poolName) : CurrencyPool(ValueMap(), poolName)
{
}

CurrencyPool::CurrencyPool(const ValueMap& properties, std::string poolName) : super(properties)
{
	this->poolName = poolName;
	this->currencies = std::vector<CurrencyData>();
}

CurrencyPool::~CurrencyPool()
{
}

void CurrencyPool::addCurrencyToPool(CurrencyData currency)
{
	this->currencies.push_back(currency);

	if (currency.currency != nullptr)
	{
		this->addChild(currency.currency);
	}
}

std::vector<Currency*> CurrencyPool::getRandomCurrencyFromPool()
{
	std::vector<Currency*> randCurrencies = std::vector<Currency*>();

	for (auto next : this->currencies)
	{
		next.currency->setCount(RandomHelper::random_int(next.minCount, next.maxCount));

		randCurrencies.push_back(next.currency);
	}

	return randCurrencies;
}
