#include "ChestPool.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ItemEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Inventory/ItemPreview.h"
#include "Objects/Platformer/Collectables/Cards/CardPools/CardPool.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

ChestPool::ChestPool(ValueMap& properties, std::string poolName, int minItems, int maxItems, CardPool* cardPool) : super(properties, poolName)
{
	this->minItems = minItems;
	this->maxItems = maxItems;
	this->cardPool = cardPool;

	if (this->cardPool != nullptr)
	{
		this->addChild(this->cardPool);
	}
}

ChestPool::~ChestPool()
{
}

std::vector<Item*> ChestPool::getChestItems()
{
	int itemCount = RandomHelper::random_int(this->minItems, this->maxItems);

	std::vector<Item*> items = this->cardPool->getCards();
	std::vector<Item*> cards = this->cardPool->getCards();

	for (auto it = cards.begin(); it != cards.end(); it++)
	{
		items.push_back(*it);
	}

	return items;
}
