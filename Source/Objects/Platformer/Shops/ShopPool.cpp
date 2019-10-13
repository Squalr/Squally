#include "ShopPool.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Inventory/ItemPreview.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

ShopPool::ShopPool(ValueMap& properties, std::string poolName, MinMaxPool* priorityPool) : super(properties, poolName)
{
	this->priorityPool = priorityPool;

	if (this->priorityPool != nullptr)
	{
		this->addChild(this->priorityPool);
	}
}

ShopPool::~ShopPool()
{
}

Item* ShopPool::getItemFromPool(bool removeSampledItem)
{
	if (this->priorityPool != nullptr)
	{
		Item* item = this->priorityPool->getItem();

		if (item != nullptr)
		{
			return item;
		}
	}

	return super::getItemFromPool(removeSampledItem);
}
