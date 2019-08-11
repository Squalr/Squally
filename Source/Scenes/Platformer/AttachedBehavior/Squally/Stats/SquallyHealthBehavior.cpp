#include "SquallyHealthBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/SaveEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string SquallyHealthBehavior::MapKeyAttachedBehavior = "squally-health";

SquallyHealthBehavior* SquallyHealthBehavior::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	SquallyHealthBehavior* instance = new SquallyHealthBehavior(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

SquallyHealthBehavior::SquallyHealthBehavior(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->squally = static_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyHealthBehavior::~SquallyHealthBehavior()
{
}

void SquallyHealthBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(SaveEvents::EventSoftSaveGameState, [=](EventCustom* eventCustom)
	{
		this->saveState();
	}));

	int maxHealth = this->squally->getStateOrDefaultInt(StateKeys::MaxHealth, 123);
	int health = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyHealth, Value(maxHealth)).asInt();

	this->squally->setState(StateKeys::Health, Value(health));
}

void SquallyHealthBehavior::saveState()
{
	SaveManager::softSaveProfileData(SaveKeys::SaveKeySquallyHealth, this->squally->getStateOrDefault(StateKeys::Health, Value(0)));
}