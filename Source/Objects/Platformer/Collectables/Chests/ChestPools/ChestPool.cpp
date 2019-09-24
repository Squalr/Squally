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

ChestPool::ChestPool(ValueMap& properties, std::string poolName, int minItems, int maxItems, CardPool* cardPool) : super(properties, poolName, cardPool)
{
	this->minItems = minItems;
	this->maxItems = maxItems;
}

ChestPool::~ChestPool()
{
}

std::vector<Item*> ChestPool::getChestItems()
{
	int itemCount = RandomHelper::random_int(this->minItems, this->maxItems);

	return this->getItemsFromPool(itemCount);
}
