#include "ShopPool.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/ShopEvents.h"
#include "Menus/Inventory/ItemPreview.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

ShopPool::ShopPool(ValueMap& initProperties, std::string poolName) : super(initProperties)
{
	this->poolName = poolName;
	this->itemPool = std::vector<std::tuple<Item*, float>>();
	this->weightSum = 0.0f;
	this->itemsNode = Node::create();

	this->addChild(this->itemsNode);
}

ShopPool::~ShopPool()
{
}

void ShopPool::onEnter()
{
	super::onEnter();
}

void ShopPool::initializePositions()
{
	super::initializePositions();
}

void ShopPool::initializeListeners()
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

Item* ShopPool::getItemFromPool()
{
	int index = RandomHelper::random_int(0, int(this->itemPool.size()) - 1);

	return std::get<0>(this->itemPool[index])->clone();
}

void ShopPool::addItemToPool(Item* item, float weight)
{
	std::tuple<Item*, float> itemAndWeight = { item, weight };

	this->itemPool.push_back(itemAndWeight);
	this->itemsNode->addChild(item);

	this->calculateWeightSum();
}

void ShopPool::calculateWeightSum()
{
	this->weightSum = 0.0f;

	for (auto it = this->itemPool.begin(); it != this->itemPool.end(); it++)
	{
		this->weightSum += std::get<1>((*it));
	}
}
