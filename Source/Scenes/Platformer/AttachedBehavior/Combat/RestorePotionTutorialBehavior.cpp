#include "RestorePotionTutorialBehavior.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/RestorePotion/RestoreHealth.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RestorePotionTutorialBehavior::MapKeyAttachedBehavior = "restore-potion-tutorial";

RestorePotionTutorialBehavior* RestorePotionTutorialBehavior::create(GameObject* owner)
{
	RestorePotionTutorialBehavior* instance = new RestorePotionTutorialBehavior(owner);

	instance->autorelease();

	return instance;
}

RestorePotionTutorialBehavior::RestorePotionTutorialBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

RestorePotionTutorialBehavior::~RestorePotionTutorialBehavior()
{
}

void RestorePotionTutorialBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventBuffApplied, [=](EventCustom* eventCustom)
	{
		CombatEvents::BuffAppliedArgs* args = static_cast<CombatEvents::BuffAppliedArgs*>(eventCustom->getUserData());

		if (args->buff != nullptr && dynamic_cast<RestoreHealth*>(args->buff) != nullptr)
		{
			dynamic_cast<RestoreHealth*>(args->buff)->enableClippy();
		}
	}));
}

void RestorePotionTutorialBehavior::onDisable()
{
	super::onDisable();
}
