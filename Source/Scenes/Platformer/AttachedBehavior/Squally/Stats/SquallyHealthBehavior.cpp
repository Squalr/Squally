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

SquallyHealthBehavior* SquallyHealthBehavior::create(GameObject* owner)
{
	SquallyHealthBehavior* instance = new SquallyHealthBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyHealthBehavior::SquallyHealthBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);
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

	int maxHealth = this->squally->getStateOrDefaultInt(StateKeys::MaxHealth, 123);
	int health = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyHealth, Value(maxHealth)).asInt();

	this->squally->setState(StateKeys::Health, Value(health));

	if (health <= 0)
	{
		this->respawn(0.1f);
	}

	if (this->squally != nullptr)
	{
		this->squally->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
		{
			if (!value.asBool())
			{
				this->respawn(1.5f);
			}
		});
	}
}

void SquallyHealthBehavior::saveState()
{
	SaveManager::softSaveProfileData(SaveKeys::SaveKeySquallyHealth, this->squally->getStateOrDefault(StateKeys::Health, Value(0)));
}

void SquallyHealthBehavior::respawn(float duration)
{
	this->runAction(Sequence::create(
		DelayTime::create(duration),
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
