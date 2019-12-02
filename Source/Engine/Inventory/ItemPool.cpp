#include "ItemPool.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ItemEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CardPools/CardPool.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

ItemPool::ItemPool(std::string poolName) : ItemPool(ValueMap(), poolName)
{
}

ItemPool::ItemPool(const ValueMap& properties, std::string poolName) : super(properties)
{
	this->poolName = poolName;
	this->itemPool = std::vector<ItemChance*>();
	this->itemsNode = Node::create();

	this->addChild(this->itemsNode);
}

ItemPool::~ItemPool()
{
}

void ItemPool::initializeListeners()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(ItemEvents::EventRequestItemFromPoolPrefix + this->poolName, [=](EventCustom* eventCustom)
	{
		ItemEvents::ItemRequestArgs* args = static_cast<ItemEvents::ItemRequestArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			args->callback(this->getItemFromPool(true));
		}
	}));
}

std::vector<Item*> ItemPool::getItemsFromPool(int count, bool removeSampledItems)
{
	std::vector<Item*> items = std::vector<Item*>();

	for (int index = 0; index < count; index++)
	{
		Item* item = this->getItemFromPool(removeSampledItems);

		if (item != nullptr)
		{
			items.push_back(item);
		}
	}

	return items;
}

Item* ItemPool::getItemFromPool(bool removeSampledItem)
{
	for (auto itemChance : this->itemPool)
	{
		float probability = itemChance->calculateProbability({ });

		if (probability > 0.0f)
		{
			float rng = RandomHelper::random_real(0.0f, 1.0f);
			
			if (rng <= probability)
			{
				Item* retItem = itemChance->getItem() == nullptr ? nullptr : itemChance->getItem()->clone();

				this->removeItemFromPool(itemChance);

				return retItem;
			}
		}
	}

	return nullptr;
}

void ItemPool::addItemToPool(ItemChance* itemChance)
{
	if (itemChance == nullptr)
	{
		return;
	}

	this->itemPool.push_back(itemChance);
	this->itemsNode->addChild(itemChance);
}

void ItemPool::removeItemFromPool(ItemChance* itemChance)
{
	this->itemPool.erase(std::remove_if(this->itemPool.begin(), this->itemPool.end(), [=](ItemChance* entry)
	{
		if (entry == itemChance)
		{
			this->itemsNode->removeChild(itemChance);

			return true;
		}

		return false;
	}), this->itemPool.end());
}
