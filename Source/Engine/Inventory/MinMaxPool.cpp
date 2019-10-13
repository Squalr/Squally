#include "MinMaxPool.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ItemEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Inventory/ItemPreview.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

MinMaxPool::MinMaxPool(const cocos2d::ValueMap& properties, std::string poolName, int minItems, int maxItems, MinMaxPool* nestedPool) : super(properties, poolName)
{
	this->itemCount = RandomHelper::random_int(minItems, maxItems);
	this->nestedPool = nestedPool;

	if (this->nestedPool != nullptr)
	{
		this->addChild(this->nestedPool);
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
	std::vector<Item*> items = this->getItemsFromPool(itemCount, true);

	if (this->nestedPool != nullptr)
	{
		std::vector<Item*> cards = this->nestedPool->getItems();

		for (auto it = cards.begin(); it != cards.end(); it++)
		{
			items.push_back(*it);
		}
	}

	return items;
}
