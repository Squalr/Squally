#include "SquallyRespawnBehavior.h"

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
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string SquallyRespawnBehavior::MapKey = "squally-respawn";

SquallyRespawnBehavior* SquallyRespawnBehavior::create(GameObject* owner)
{
	SquallyRespawnBehavior* instance = new SquallyRespawnBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyRespawnBehavior::SquallyRespawnBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);
	this->spawnCoords = Vec2::ZERO;

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyRespawnBehavior::~SquallyRespawnBehavior()
{
}

void SquallyRespawnBehavior::onLoad()
{
	this->spawnCoords = GameUtils::getWorldCoords(this->squally);

	if (this->squally != nullptr)
	{
		this->squally->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
		{
			if (!value.asBool())
			{
				this->respawn(1.5f);
			}
		});
	}
}

void SquallyRespawnBehavior::onDisable()
{
	super::onDisable();
}

void SquallyRespawnBehavior::respawn(float duration)
{
	this->runAction(Sequence::create(
		DelayTime::create(duration),
		CallFunc::create([=]()
		{
			if (this->spawnCoords != Vec2::ZERO)
			{
				const Vec2 SpawnOffset = Vec2(0.0f, 64.0f);

				PlatformerEvents::TriggerWarpToLocation(PlatformerEvents::WarpArgs(this->squally, this->spawnCoords + SpawnOffset));
			}
			
			this->squally->getAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
			{
				healthBehavior->revive();
			});
		}),
		nullptr
	));
}

