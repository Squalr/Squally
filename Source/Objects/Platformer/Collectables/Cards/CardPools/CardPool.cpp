#include "CardPool.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

CardPool::CardPool(int maxCards) : super()
{
	this->maxCards = maxCards;
}

CardPool::~CardPool()
{
}
