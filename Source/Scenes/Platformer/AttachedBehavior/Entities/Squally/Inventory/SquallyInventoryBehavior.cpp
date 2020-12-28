#include "SquallyInventoryBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/SaveEvents.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string SquallyInventoryBehavior::MapKey = "squally-inventory";

SquallyInventoryBehavior* SquallyInventoryBehavior::create(GameObject* owner)
{
	SquallyInventoryBehavior* instance = new SquallyInventoryBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyInventoryBehavior::SquallyInventoryBehavior(GameObject* owner) : super(owner, SaveKeys::SaveKeySquallyInventory, SaveKeys::SaveKeySquallyEquipment, SaveKeys::SaveKeySquallyCurrencyInventory)
{
	this->squally = dynamic_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyInventoryBehavior::~SquallyInventoryBehavior()
{
}

void SquallyInventoryBehavior::onLoad()
{
}

void SquallyInventoryBehavior::onDisable()
{
	super::onDisable();
}

void SquallyInventoryBehavior::saveState()
{
}
