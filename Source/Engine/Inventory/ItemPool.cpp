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
	this->probabilityCache = std::vector<ProbabilityData>();
	this->probabilitySum = 0.0f;
	this->cacheDirty = true;

	this->addChild(this->itemsNode);
}

ItemPool::~ItemPool()
{
}

void ItemPool::initializeListeners()
{
	super::initializeListeners();
	
	this->addEventListenerIgnorePause(EventListenerCustom::create(ItemEvents::EventRequestItemFromPoolPrefix + this->poolName, [=](EventCustom* eventCustom)
	{
		ItemEvents::ItemRequestArgs* args = static_cast<ItemEvents::ItemRequestArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			args->callback(this->getItemFromPool(true, args->inventories));
		}
	}));
}

int ItemPool::getPoolSize()
{
	return this->itemPool.size();
}

std::vector<Item*> ItemPool::getItemsFromPool(int count, std::vector<Inventory*> inventories, bool removeSampledItems)
{
	std::vector<Item*> items = std::vector<Item*>();

	for (int index = 0; index < count; index++)
	{
		Item* item = this->getItemFromPool(removeSampledItems, inventories);

		if (item != nullptr)
		{
			items.push_back(item);
		}
	}

	return items;
}

std::vector<Item*> ItemPool::getItemsFromPoolGuaranteed(int count, std::vector<Inventory*> inventories, bool removeSampledItems)
{
	std::vector<Item*> items = std::vector<Item*>();

	for (int index = 0; index < count; index++)
	{
		Item* item = this->getItemFromPoolGuaranteed(removeSampledItems, inventories);

		if (item != nullptr)
		{
			items.push_back(item);
		}
	}

	return items;
}

Item* ItemPool::getItemFromPool(bool removeSampledItem, std::vector<Inventory*> inventories)
{
	for (auto itemChance : this->itemPool)
	{
		float probability = itemChance->calculateProbability(inventories);

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

Item* ItemPool::getItemFromPoolGuaranteed(bool removeSampledItem, std::vector<Inventory*> inventories)
{
	if (this->cacheDirty)
	{
		this->cacheDirty = false;
		this->probabilitySum = 0.0f;
		this->probabilityCache.clear();

		for (auto itemChance : this->itemPool)
		{
			float probability = itemChance->calculateProbability(inventories);

			this->probabilitySum += probability;

			this->probabilityCache.push_back(ProbabilityData(itemChance, probability));
		}
	}

	float sample = RandomHelper::random_real(0.0f, this->probabilitySum);
	float currentSum = 0.0f;

	for (auto probabilityData : this->probabilityCache)
	{
		currentSum += probabilityData.probability;

		if (sample <= currentSum && probabilityData.probability > 0.0f)
		{
			Item* retItem = probabilityData.itemChance->getItem() == nullptr ? nullptr : probabilityData.itemChance->getItem()->clone();

			this->removeItemFromPool(probabilityData.itemChance);

			return retItem;
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

	this->cacheDirty = true;
	this->itemPool.push_back(itemChance);
	this->itemsNode->addChild(itemChance);
}

void ItemPool::removeItemFromPool(ItemChance* itemChance)
{
	this->itemPool.erase(std::remove_if(this->itemPool.begin(), this->itemPool.end(), [=](ItemChance* entry)
	{
		if (entry == itemChance)
		{
			this->cacheDirty = true;
			this->itemsNode->removeChild(itemChance);

			return true;
		}

		return false;
	}), this->itemPool.end());
}
