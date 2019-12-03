#include "MinMaxPool.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ItemEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

MinMaxPool::MinMaxPool(const cocos2d::ValueMap& properties, std::string poolName, SampleMethod sampleMethod, int minItems, int maxItems, std::vector<MinMaxPool*> nestedPools) : super(properties, poolName)
{
	this->itemCount = RandomHelper::random_int(minItems, maxItems);
	this->nestedPools = std::vector<MinMaxPool*>();
	this->sampleMethod = sampleMethod;

	for (auto nestedPool : this->nestedPools)
	{
		this->addChild(nestedPool);
	}
}

MinMaxPool::~MinMaxPool()
{
}

Item* MinMaxPool::getItem()
{
	if (this->itemCount <= 0)
	{
		return nullptr;
	}

	this->itemCount--;

	return this->getItemFromPool(true);
}

std::vector<Item*> MinMaxPool::getItems()
{
	std::vector<Item*> items = std::vector<Item*>();
	
	switch (this->sampleMethod)
	{
		default:
		case SampleMethod::Unbounded:
		{
			for (auto item : this->getItemsFromPool(this->getPoolSize(), true))
			{
				items.push_back(item);
			}

			break;
		}
		case SampleMethod::Random:
		{
			for (auto item : this->getItemsFromPool(itemCount, true))
			{
				items.push_back(item);
			}

			break;
		}
		case SampleMethod::Guarantee:
		{
			for (auto item : this->getItemsFromPoolGuaranteed(itemCount, true))
			{
				items.push_back(item);
			}

			break;
		}
	}

	for (auto nestedPool : this->nestedPools)
	{
		for (auto item : nestedPool->getItems())
		{
			items.push_back(item);
		}
	}

	return items;
}
