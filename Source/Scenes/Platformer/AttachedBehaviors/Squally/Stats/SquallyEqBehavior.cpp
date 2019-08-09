#include "SquallyEqBehavior.h"

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

const std::string SquallyEqBehavior::MapKeyAttachedBehavior = "squally-eq";

SquallyEqBehavior* SquallyEqBehavior::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	SquallyEqBehavior* instance = new SquallyEqBehavior(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

SquallyEqBehavior::SquallyEqBehavior(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
}

SquallyEqBehavior::~SquallyEqBehavior()
{
}

void SquallyEqBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(SaveEvents::EventSoftSaveGameState, [=](EventCustom* eventCustom)
	{
		this->saveState();
	}));

	this->setEq(SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyEq, Value(SquallyEqBehavior::DefaultEq)).asInt());
	this->setEqExperience(SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyEqExperience, Value(this->getEqExperience())).asInt());
}

void SquallyEqBehavior::saveState()
{
	SaveManager::softSaveProfileData(SaveKeys::SaveKeySquallyEqExperience, Value(this->getEqExperience()));
	SaveManager::softSaveProfileData(SaveKeys::SaveKeySquallyEq, Value(this->getEq()));
}