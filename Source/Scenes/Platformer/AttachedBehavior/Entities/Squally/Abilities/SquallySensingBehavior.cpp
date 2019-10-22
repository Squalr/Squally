#include "SquallySensingBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/HackableEvents.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityRuneBehavior.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;


SquallySensingBehavior* SquallySensingBehavior::create(GameObject* owner)
{
	SquallySensingBehavior* instance = new SquallySensingBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallySensingBehavior::SquallySensingBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallySensingBehavior::~SquallySensingBehavior()
{
}

void SquallySensingBehavior::onLoad()
{
	this->squally->whenKeyReleased({ EventKeyboard::KeyCode::KEY_SHIFT }, [=](InputEvents::InputArgs* args)
	{
		HackableEvents::TriggerSensingDisable();
	});
	
	this->squally->whenKeyReleasedHackerMode({ EventKeyboard::KeyCode::KEY_SHIFT }, [=](InputEvents::InputArgs* args)
	{
		HackableEvents::TriggerSensingDisable();
	});
	
	this->squally->whenKeyPressed({ EventKeyboard::KeyCode::KEY_SHIFT }, [=](InputEvents::InputArgs* args)
	{
		HackableEvents::TriggerSensingEnable(HackableEvents::SensingArgs(this->squally->getStateOrDefaultInt(StateKeys::Eq, 1)));
	});
}
