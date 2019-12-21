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
	this->nestedPools = nestedPools;
	this->sampleMethod = sampleMethod;

	for (auto nestedPool : this->nestedPools)
	{
		this->addChild(nestedPool);
	}
}

MinMaxPool::~MinMaxPool()
{
}

Item* MinMaxPool::getItem(std::vector<Inventory*> inventories)
{
	if (this->sampleMethod != SampleMethod::Unbounded)
	{
		if (this->itemCount <= 0)
		{
			return nullptr;
		}

		this->itemCount--;
	}

	return this->getItemFromPool(true, inventories);
}

std::vector<Item*> MinMaxPool::getItems(std::vector<Inventory*> inventories)
{
	std::vector<Item*> items = std::vector<Item*>();

	for (auto nestedPool : this->nestedPools)
	{
		for (auto item : nestedPool->getItems(inventories))
		{
			items.push_back(item);
		}
	}
	
	switch (this->sampleMethod)
	{
		default:
		case SampleMethod::Unbounded:
		{
			for (auto item : this->getItemsFromPool(this->getPoolSize(), inventories, true))
			{
				items.push_back(item);
			}

			break;
		}
		case SampleMethod::Random:
		{
			for (auto item : this->getItemsFromPool(itemCount, inventories, true))
			{
				items.push_back(item);
			}

			break;
		}
		case SampleMethod::Guarantee:
		{
			for (auto item : this->getItemsFromPoolGuaranteed(itemCount, inventories, true))
			{
				items.push_back(item);
			}

			break;
		}
	}

	return items;
}
