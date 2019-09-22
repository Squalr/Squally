#include "CardPool.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

CardPool::CardPool() : super()
{
	this->itemPool = std::vector<std::tuple<HexusCard*, float>>();
	this->weightSum = 0.0f;
	this->cardsNode = Node::create();

	this->addChild(this->cardsNode);
}

CardPool::~CardPool()
{
}

void CardPool::onEnter()
{
	super::onEnter();
}

void CardPool::initializePositions()
{
	super::initializePositions();
}

void CardPool::initializeListeners()
{
	super::initializeListeners();
}

HexusCard* CardPool::getCardFromPool()
{
	// TODO: this is uniform and needs to account for weights
	int index = RandomHelper::random_int(0, int(this->itemPool.size()) - 1);

	return static_cast<HexusCard*>(std::get<0>(this->itemPool[index])->clone());
}

void CardPool::addCardToPool(HexusCard* item, float weight)
{
	std::tuple<HexusCard*, float> itemAndWeight = { item, weight };

	this->itemPool.push_back(itemAndWeight);
	this->cardsNode->addChild(item);

	this->calculateWeightSum();
}

void CardPool::calculateWeightSum()
{
	this->weightSum = 0.0f;

	for (auto it = this->itemPool.begin(); it != this->itemPool.end(); it++)
	{
		this->weightSum += std::get<1>((*it));
	}
}
