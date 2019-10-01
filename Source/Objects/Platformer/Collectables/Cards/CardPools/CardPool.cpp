#include "CardPool.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

CardPool::CardPool(int minCards, int maxCards) : super()
{
	this->remainingCards = RandomHelper::random_int(minCards, maxCards);
}

CardPool::~CardPool()
{
}

Item* CardPool::getCard()
{
	if (this->remainingCards-- <= 0)
	{
		return nullptr;
	}

	return this->getItemFromPool();
}

std::vector<Item*> CardPool::getCards()
{
	int count = this->remainingCards;
	
	this->remainingCards = 0;

	this->removeAllMaxedOutCardsFromPool();

	return this->getItemsFromPool(count);
}

void CardPool::removeAllMaxedOutCardsFromPool()
{

}
