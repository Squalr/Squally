#include "SquallyManaBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/SaveEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/PlatformerEntity.h"
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

	this->setMana(SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyMana, Value(0)).asInt());
}

void SquallyManaBehavior::saveState()
{
	this->setMana(SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyMana, Value(this->getMana())).asInt());
	SaveManager::softSaveProfileData(SaveKeys::SaveKeySquallyMana, Value(this->getMana()));
}