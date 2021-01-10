#include "SquallyHackingBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/HackableEvents.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityRuneBehavior.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;


SquallyHackingBehavior* SquallyHackingBehavior::create(GameObject* owner)
{
	SquallyHackingBehavior* instance = new SquallyHackingBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyHackingBehavior::SquallyHackingBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);
	
	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyHackingBehavior::~SquallyHackingBehavior()
{
}

void SquallyHackingBehavior::onLoad()
{
	this->squally->watchForAttachedBehavior<EntityRuneBehavior>([=](EntityRuneBehavior* runeBehavior)
	{
		this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventForceUseHackerMode, [=](EventCustom*)
		{
			runeBehavior->tryUseRune();
		}));

		this->squally->whenKeyPressed({ InputEvents::KeyCode::KEY_TAB }, [=](InputEvents::KeyboardEventArgs* args)
		{
			HackerModeQueryArgs queryArgs = HackerModeQueryArgs();

			HackableEvents::TriggerQueryHackerModeAllowed(&queryArgs);
			
			if (queryArgs.hackerModeAllowed && runeBehavior->tryUseRune())
			{
				args->handle();
				this->toggleHackerMode();
			}
		});
	});

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventForceUseHackerMode, [=](EventCustom*)
	{
		this->toggleHackerMode();
	}));

	this->squally->whenKeyPressedHackerMode({ InputEvents::KeyCode::KEY_TAB, InputEvents::KeyCode::KEY_ESCAPE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		args->handle();

		this->toggleHackerMode();
	});

	HackableObject::SetHackFlags(HackFlagUtils::GetCurrentHackFlags());
}

void SquallyHackingBehavior::onDisable()
{
	super::onDisable();
}

void SquallyHackingBehavior::toggleHackerMode()
{
	HackableEvents::TriggerHackerModeToggle(HackToggleArgs());
}
