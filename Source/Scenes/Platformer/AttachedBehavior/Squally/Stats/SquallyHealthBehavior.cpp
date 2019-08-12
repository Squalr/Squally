#include "SquallyHealthBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
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
	this->spawnCoords = Vec2::ZERO;

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
	this->spawnCoords = this->squally->getPosition();

	this->addEventListenerIgnorePause(EventListenerCustom::create(SaveEvents::EventSoftSaveGameState, [=](EventCustom* eventCustom)
	{
		this->saveState();
	}));

	this->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (!value.asBool())
		{
			this->respawn();
		}
	});

	int maxHealth = this->squally->getStateOrDefaultInt(StateKeys::MaxHealth, 123);
	int health = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyHealth, Value(maxHealth)).asInt();

	this->squally->setState(StateKeys::Health, Value(health));
}

void SquallyHealthBehavior::saveState()
{
	SaveManager::softSaveProfileData(SaveKeys::SaveKeySquallyHealth, this->squally->getStateOrDefault(StateKeys::Health, Value(0)));
}

void SquallyHealthBehavior::respawn()
{
	this->runAction(Sequence::create(
		DelayTime::create(1.5f),
		CallFunc::create([=]()
		{
			if (this->spawnCoords != Vec2::ZERO)
			{
				this->squally->setPosition(this->spawnCoords);
			}
			
			this->squally->setState(StateKeys::IsAlive, Value(true));
		}),
		nullptr
	));
}
