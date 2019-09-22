#include "ChestPool.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/ShopEvents.h"
#include "Menus/Inventory/ItemPreview.h"
#include "Objects/Platformer/Collectables/Cards/CardPools/CardPool.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

ChestPool::ChestPool(ValueMap& properties, std::string poolName, int minItems, int maxItems, CardPool* cardPool) : super(properties)
{
	this->poolName = poolName;
	this->minItems = minItems;
	this->maxItems = maxItems;
	this->cardPool = cardPool;
	this->itemPool = std::vector<std::tuple<Item*, float>>();
	this->weightSum = 0.0f;
	this->itemsNode = Node::create();

	if (this->cardPool != nullptr)
	{
		this->addChild(this->cardPool);
	}

	this->addChild(this->itemsNode);
}

ChestPool::~ChestPool()
{
}

void ChestPool::onEnter()
{
	super::onEnter();
}

void ChestPool::initializePositions()
{
	super::initializePositions();
}

void ChestPool::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(ShopEvents::EventRequestItemFromPoolPrefix + this->poolName, [=](EventCustom* eventCustom)
	{
		ShopEvents::ItemRequestArgs* args = static_cast<ShopEvents::ItemRequestArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			args->callback(this->getItemFromPool());
		}
	}));
}

std::vector<Item*> ChestPool::getItemsFromPool()
{
	int itemCount = RandomHelper::random_int(this->minItems, this->maxItems);
	std::vector<Item*> items = std::vector<Item*>();

	// Always include a hexus card!
	if (this->cardPool != nullptr)
	{
		HexusCard* hexusCard = this->cardPool->getCardFromPool();

		if (hexusCard != nullptr)
		{
			items.push_back(hexusCard);
		}
	}

	for (int index = 0; index < itemCount; index++)
	{
		items.push_back(this->getItemFromPool());
	}

	return items;
}

Item* ChestPool::getItemFromPool()
{
	// TODO: this is uniform and needs to account for weights
	int index = RandomHelper::random_int(0, int(this->itemPool.size()) - 1);

	return std::get<0>(this->itemPool[index])->clone();
}

void ChestPool::addItemToPool(Item* item, float weight)
{
	std::tuple<Item*, float> itemAndWeight = { item, weight };

	this->itemPool.push_back(itemAndWeight);
	this->itemsNode->addChild(item);

	this->calculateWeightSum();
}

void ChestPool::calculateWeightSum()
{
	this->weightSum = 0.0f;

	for (auto it = this->itemPool.begin(); it != this->itemPool.end(); it++)
	{
		this->weightSum += std::get<1>((*it));
	}
}
