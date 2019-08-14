#include "SquallyRuneBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/SaveEvents.h"
#include "Engine/Input/Input.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityRuneBehavior.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyRuneBehavior::MapKeyAttachedBehavior = "squally-rune";

SquallyRuneBehavior* SquallyRuneBehavior::create(GameObject* owner)
{
	SquallyRuneBehavior* instance = new SquallyRuneBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyRuneBehavior::SquallyRuneBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyRuneBehavior::~SquallyRuneBehavior()
{
}

void SquallyRuneBehavior::onLoad()
{
	// Not the ideal way to communicate between attached behavior, but this is easiest
	this->entityRuneBehavior = this->squally->getAttachedBehavior<EntityRuneBehavior>();

	this->addEventListenerIgnorePause(EventListenerCustom::create(SaveEvents::EventSoftSaveGameState, [=](EventCustom* eventCustom)
	{
		this->saveState();
	}));

	this->addEventListener(EventListenerCustom::create(HackableEvents::EventForceHackerModeEnable, [=](EventCustom*)
	{
		this->entityRuneBehavior->tryUseRune();
		
		HackableEvents::TriggerHackerModeToggle(HackableEvents::HackToggleArgs(this->squally->getStateOrDefaultInt(StateKeys::Eq, 1)));
	}));

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_TAB }, [=](InputEvents::InputArgs* args)
	{
		args->handle();
		
		if (this->entityRuneBehavior->tryUseRune())
		{
			HackableEvents::TriggerHackerModeToggle(HackableEvents::HackToggleArgs(this->squally->getStateOrDefaultInt(StateKeys::Eq, 1)));
		}
	});

	ValueVector cooldowns = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyRuneCooldowns, Value(ValueVector())).asValueVector();

	for (int index = 0; index < std::min((int)cooldowns.size(), EntityRuneBehavior::MaxRunes); index++)
	{
		this->entityRuneBehavior->setRuneCooldown(index, cooldowns[index].asFloat());
	}
}

void SquallyRuneBehavior::saveState()
{
	ValueVector cooldowns = ValueVector();

	for (int index = 0; index < EntityRuneBehavior::MaxRunes; index++)
	{
		cooldowns.push_back(Value(this->entityRuneBehavior->getRuneCooldown(index)));
	}

	SaveManager::softSaveProfileData(SaveKeys::SaveKeySquallyRuneCooldowns, Value(cooldowns));
}
