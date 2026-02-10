#include "IncrementHealthFlaskTutorialBehavior.h"

#include "2d/CCActionEase.h"
#include "2d/CCActionInstant.h"
#include "2d/CCActionInterval.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCValue.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Hackables/ScrappyClippy.h"
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
		CombatEvents::BuffAppliedArgs* args = static_cast<CombatEvents::BuffAppliedArgs*>(eventCustom->getData());

		if (args != nullptr && args->buff != nullptr && dynamic_cast<IncrementHealth*>(args->buff) != nullptr)
		{
			args->buff->registerClippyOnto(IncrementHealth::IncrementHealthIdentifier, [=]
			{
				return ScrappyClippy::create(Strings::Menus_Hacking_ClippyHelp_Items_IncrementHealthFlask_IncrementHealthInc::create());
			});
		}
	}));
}

void IncrementHealthFlaskTutorialBehavior::onDisable()
{
	super::onDisable();
}
