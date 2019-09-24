#include "ShopPool.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Inventory/ItemPreview.h"
#include "Objects/Platformer/Collectables/Cards/CardPools/CardPool.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

ShopPool::ShopPool(ValueMap& properties, std::string poolName, CardPool* cardPool) : super(properties, poolName)
{
	this->cardPool = cardPool;

	if (this->cardPool != nullptr)
	{
		this->addChild(this->cardPool);
	}
}

ShopPool::~ShopPool()
{
}

Item* ShopPool::getItemFromPool()
{
	if (this->cardPool != nullptr)
	{
		Item* card = this->cardPool->getCard();

		if (card != nullptr)
		{
			return card;
		}
	}

	return super::getItemFromPool();
}
