#include "LockedPortal.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/InventoryEvents.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Sound/Sound.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
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
	this->portal = dynamic_cast<Portal*>(owner);
	this->requiredItemName = "";
	this->playerInventory = Inventory::create(SaveKeys::SaveKeySquallyInventory);

	if (this->portal == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->playerInventory);
}

LockedPortal::~LockedPortal()
{
}

void LockedPortal::onLoad()
{
	this->requiredItemName = this->portal->getPropertyOrDefault(LockedPortal::MapKeyPropertyItemRequired, Value("")).asString();

	if (!this->requiredItemName.empty())
	{
		this->playerInventory->onInventoryChanged([=]()
		{
			this->checkForRequiredItem();
		});

		this->checkForRequiredItem();
	}
}

void LockedPortal::checkForRequiredItem()
{
	std::vector<Item*> items = this->playerInventory->getItems();

	this->portal->lock();

	for (auto it = items.begin(); it != items.end(); it++)
	{
		if (*it != nullptr && this->requiredItemName == (*it)->getItemName())
		{
			this->portal->unlock();
		}
	}
}
