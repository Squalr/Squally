#include "SquallyHealthBehavior.h"

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

const std::string SquallyHealthBehavior::MapKeyAttachedBehavior = "squally-health";

SquallyHealthBehavior* SquallyHealthBehavior::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	SquallyHealthBehavior* instance = new SquallyHealthBehavior(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

SquallyHealthBehavior::SquallyHealthBehavior(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
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

	this->setHealth(SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyHealth, Value(0)).asInt());
}

void SquallyHealthBehavior::saveState()
{
	this->setHealth(SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyHealth, Value(this->getHealth())).asInt());
	SaveManager::softSaveProfileData(SaveKeys::SaveKeySquallyHealth, Value(this->getHealth()));
}