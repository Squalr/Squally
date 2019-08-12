#include "SquallyManaBehavior.h"

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

const std::string SquallyManaBehavior::MapKeyAttachedBehavior = "squally-mana";

SquallyManaBehavior* SquallyManaBehavior::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	SquallyManaBehavior* instance = new SquallyManaBehavior(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

SquallyManaBehavior::SquallyManaBehavior(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->squally = dynamic_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyManaBehavior::~SquallyManaBehavior()
{
}

void SquallyManaBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(SaveEvents::EventSoftSaveGameState, [=](EventCustom* eventCustom)
	{
		this->saveState();
	}));

	int maxMana = this->squally->getStateOrDefaultInt(StateKeys::MaxMana, 123);
	int mana = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyMana, Value(maxMana)).asInt();

	this->squally->setState(StateKeys::Mana, Value(mana));
}

void SquallyManaBehavior::saveState()
{
	SaveManager::softSaveProfileData(SaveKeys::SaveKeySquallyMana, this->squally->getStateOrDefault(StateKeys::Mana, Value(0)));
}
