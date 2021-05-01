#include "SquallyCombatRespawnBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/SaveEvents.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerHelper.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
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
		CombatEvents::BeforeReturnToMapArgs* args = static_cast<CombatEvents::BeforeReturnToMapArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			if (args->defeat)
			{
				SaveManager::SoftDeleteProfileData(SaveKeys::SaveKeySquallyPositionX);
				SaveManager::SoftDeleteProfileData(SaveKeys::SaveKeySquallyPositionY);
				SaveManager::SoftDeleteProfileData(SaveKeys::SaveKeySquallyPositionZ);
				SaveManager::SoftDeleteProfileData(SaveKeys::SaveKeySquallyLayerId);
			}

			this->respawn(!args->defeat);
		}
	}));
}

void SquallyCombatRespawnBehavior::onDisable()
{
	super::onDisable();
}

void SquallyCombatRespawnBehavior::respawn(bool softRevive)
{
	ObjectEvents::QueryObjects<PlatformerHelper>([&](PlatformerHelper* helper)
	{
		helper->getComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
		{
			if (healthBehavior->isDead())
			{
				if (softRevive)
				{
					// No soft revive for helpers
				}
				else
				{
					// Always revive squally on defeat
					healthBehavior->revive();
				}
			}
		});
	});

	this->squally->getComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
	{
		if (healthBehavior->isDead())
		{
			if (softRevive)
			{
				// Revive squally to 1hp on victory
				healthBehavior->setHealth(1, false);
			}
			else
			{
				// Always revive squally on defeat
				healthBehavior->revive();
			}
		}
	});
}

