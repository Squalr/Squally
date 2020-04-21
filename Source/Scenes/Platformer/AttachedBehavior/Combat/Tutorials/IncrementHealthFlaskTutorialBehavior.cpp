#include "IncrementHealthFlaskTutorialBehavior.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/IncrementHealth.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string IncrementHealthFlaskTutorialBehavior::MapKey = "increment-health-tutorial";

IncrementHealthFlaskTutorialBehavior* IncrementHealthFlaskTutorialBehavior::create(GameObject* owner)
{
	IncrementHealthFlaskTutorialBehavior* instance = new IncrementHealthFlaskTutorialBehavior(owner);

	instance->autorelease();

	return instance;
}

IncrementHealthFlaskTutorialBehavior::IncrementHealthFlaskTutorialBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

IncrementHealthFlaskTutorialBehavior::~IncrementHealthFlaskTutorialBehavior()
{
}

void IncrementHealthFlaskTutorialBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventBuffApplied, [=](EventCustom* eventCustom)
	{
		CombatEvents::BuffAppliedArgs* args = static_cast<CombatEvents::BuffAppliedArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->buff != nullptr && dynamic_cast<IncrementHealth*>(args->buff) != nullptr)
		{
		}
	}));
}

void IncrementHealthFlaskTutorialBehavior::onDisable()
{
	super::onDisable();
}
