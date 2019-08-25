#include "SquallyHackingBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/HackableEvents.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityRuneBehavior.h"
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
	this->entityRuneBehavior = this->squally->getAttachedBehavior<EntityRuneBehavior>();

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventForceHackerModeEnable, [=](EventCustom*)
	{
		if (this->entityRuneBehavior != nullptr)
		{
			this->entityRuneBehavior->tryUseRune();
		}
		
		HackableEvents::TriggerHackerModeToggle(HackableEvents::HackToggleArgs(this->squally->getStateOrDefaultInt(StateKeys::Eq, 1)));
	}));

	this->squally->whenKeyPressed({ EventKeyboard::KeyCode::KEY_TAB }, [=](InputEvents::InputArgs* args)
	{
		args->handle();

		HackableEvents::HackerModeQueryArgs queryArgs = HackableEvents::HackerModeQueryArgs();

		HackableEvents::TriggerQueryHackerModeAllowed(&queryArgs);
		
		if (queryArgs.hackerModeAllowed && (this->entityRuneBehavior == nullptr || this->entityRuneBehavior->tryUseRune()))
		{
			HackableEvents::TriggerHackerModeToggle(HackableEvents::HackToggleArgs(this->squally->getStateOrDefaultInt(StateKeys::Eq, 1)));
		}
	});

	this->squally->whenKeyPressedHackerMode({ EventKeyboard::KeyCode::KEY_TAB, EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		args->handle();

		HackableEvents::TriggerHackerModeToggle(HackableEvents::HackToggleArgs(this->squally->getStateOrDefaultInt(StateKeys::Eq, 1)));
	});
}
