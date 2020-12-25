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
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/HelperManagerBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
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
	this->squally = static_cast<Squally*>(owner);
	this->isRespawning = false;

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

	this->scheduleEvery([=]()
	{
		if (!this->squally->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			this->respawn(1.5f);
		}
	}, 1.0f / 15.0f);
}

void SquallyRespawnBehavior::onDisable()
{
	super::onDisable();
}

void SquallyRespawnBehavior::respawn(float duration)
{
	if (this->isRespawning)
	{
		return;
	}

	this->isRespawning = true;

	PlatformerEvents::TriggerBeforeLoadRespawn();
	
	if (duration <= 0.0f)
	{
		this->doRespawn();
	}
	else
	{
		this->runAction(Sequence::create(
			DelayTime::create(duration),
			CallFunc::create([=]()
			{
				this->doRespawn();
			}),
			nullptr
		));
	}
}

void SquallyRespawnBehavior::doRespawn()
{
	this->squally->getAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
	{
		healthBehavior->revive();
	});

	this->squally->getAttachedBehavior<HelperManagerBehavior>([=](HelperManagerBehavior* helperManagerBehavior)
	{
		PlatformerEntity* helper = helperManagerBehavior->getHelperRef();

		if (helper != nullptr)
		{
			helper->getAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
			{
				healthBehavior->revive();
			});
		}
	});

	PlatformerEvents::TriggerLoadRespawn();

	this->isRespawning = false;
}

