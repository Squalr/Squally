#include "SquallyCombatRespawnBehavior.h"

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
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string SquallyCombatRespawnBehavior::MapKey = "squally-combat-respawn";

SquallyCombatRespawnBehavior* SquallyCombatRespawnBehavior::create(GameObject* owner)
{
	SquallyCombatRespawnBehavior* instance = new SquallyCombatRespawnBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyCombatRespawnBehavior::SquallyCombatRespawnBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyCombatRespawnBehavior::~SquallyCombatRespawnBehavior()
{
}

void SquallyCombatRespawnBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventBeforeReturnToMap, [=](EventCustom* eventCustom)
	{
		CombatEvents::BeforeReturnToMapArgs* args = static_cast<CombatEvents::BeforeReturnToMapArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			if (args->defeat)
			{
				SaveManager::softDeleteProfileData(SaveKeys::SaveKeySquallyPositionX);
				SaveManager::softDeleteProfileData(SaveKeys::SaveKeySquallyPositionY);
				SaveManager::softDeleteProfileData(SaveKeys::SaveKeySquallyPositionZ);
			}
		
			this->squally->getAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
			{
				if (args->defeat)
				{
					// Always revive squally on defeat
					healthBehavior->revive();
				}
				else if (healthBehavior->isDead())
				{
					// Revive squally to 1hp on victory
					healthBehavior->setHealth(1, false);
				}
			});
		}
	}));
}

void SquallyCombatRespawnBehavior::onDisable()
{
	super::onDisable();
}

void SquallyCombatRespawnBehavior::respawn()
{
}

