#include "LockedPortal.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/InventoryEvents.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

using namespace cocos2d;

const std::string LockedPortal::MapKeyAttachedBehavior = "locked-portal";
const std::string LockedPortal::MapKeyPropertyItemRequired = "item-required";

LockedPortal* LockedPortal::create(GameObject* owner)
{
	LockedPortal* instance = new LockedPortal(owner);

	instance->autorelease();

	return instance;
}

LockedPortal::LockedPortal(GameObject* owner) : super(owner)
{
	this->playerInventory = nullptr;
	this->portal = dynamic_cast<Portal*>(owner);
	this->requiredItemName = "";

	if (this->portal == nullptr)
	{
		this->invalidate();
	}
}

LockedPortal::~LockedPortal()
{
}

void LockedPortal::onLoad()
{
	this->requiredItemName = this->portal->getPropertyOrDefault(LockedPortal::MapKeyPropertyItemRequired, Value("")).asString();

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		squally->watchForAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
		{
			this->playerInventory = entityInventoryBehavior->getInventory();

			if (this->playerInventory != nullptr && !this->requiredItemName.empty())
			{
				this->playerInventory->onInventoryChanged([=]()
				{
					this->checkForRequiredItem();
				});

				this->checkForRequiredItem();
			}
		});
	}, Squally::MapKeySqually);
}

void LockedPortal::checkForRequiredItem()
{
	this->portal->lock();

	if (this->playerInventory == nullptr)
	{
		return;
	}

	for (auto item : this->playerInventory->getItems())
	{
		if (item != nullptr && this->requiredItemName == item->getItemName())
		{
			this->portal->unlock();
		}
	}
}
