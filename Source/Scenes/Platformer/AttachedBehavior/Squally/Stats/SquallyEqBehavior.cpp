#include "SquallyEqBehavior.h"

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

const std::string SquallyEqBehavior::MapKeyAttachedBehavior = "squally-eq";

SquallyEqBehavior* SquallyEqBehavior::create(GameObject* owner)
{
	SquallyEqBehavior* instance = new SquallyEqBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyEqBehavior::SquallyEqBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
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

	int defaultEqExp = this->squally->getStateOrDefaultInt(StateKeys::EqExperience, 0);
	int eq = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyEq, Value(1)).asInt();
	int eqExp = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyEqExperience, Value(defaultEqExp)).asInt();

	this->squally->setState(StateKeys::Eq, Value(eq));
	this->squally->setState(StateKeys::EqExperience, Value(eqExp));
}

void SquallyEqBehavior::saveState()
{
	SaveManager::softSaveProfileData(SaveKeys::SaveKeySquallyEqExperience, this->squally->getStateOrDefault(StateKeys::EqExperience, Value(0)));
	SaveManager::softSaveProfileData(SaveKeys::SaveKeySquallyEq, this->squally->getStateOrDefault(StateKeys::Eq, Value(1)));
}