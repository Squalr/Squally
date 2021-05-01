#include "RewardPool.h"

#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

RewardPool::RewardPool(ValueMap& properties, std::string poolName, std::vector<MinMaxPool*> nestedPools) : super(properties, poolName, SampleMethod::Unbounded, 1, 1, nestedPools)
{
	this->itemsNode = Node::create();
	this->items = std::vector<Item*>();
	this->properties[GameObject::MapKeyQueryable] = false;

	this->addChild(this->itemsNode);
}

RewardPool::~RewardPool()
{
}

void RewardPool::onEnter()
{
	super::onEnter();
	
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		squally->getComponent<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
		{
			this->items = this->getItems(entityInventoryBehavior->getAllInventories());

			for (auto item : this->items)
			{
				this->itemsNode->addChild(item);
			}

			// Re-enable querying. This prevents a race-scenario where an object queries this one before items are built.
			this->properties[GameObject::MapKeyQueryable] = true;
		});
	}, Squally::MapKey);
}

void RewardPool::initializePositions()
{
	super::initializePositions();
}

void RewardPool::initializeListeners()
{
	super::initializeListeners();
}

Item* RewardPool::getNextItem()
{
	if (this->items.empty())
	{
		return nullptr;
	}

	Item* item = this->items.back();

	this->items.pop_back();

	return item->clone();
}
