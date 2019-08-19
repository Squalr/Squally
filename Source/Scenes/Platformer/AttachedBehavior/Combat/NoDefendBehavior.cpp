#include "NoDefendBehavior.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

const std::string NoDefendBehavior::MapKeyAttachedBehavior = "no-defend";

NoDefendBehavior* NoDefendBehavior::create(GameObject* owner)
{
	NoDefendBehavior* instance = new NoDefendBehavior(owner);

	instance->autorelease();

	return instance;
}

NoDefendBehavior::NoDefendBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

NoDefendBehavior::~NoDefendBehavior()
{
}

void NoDefendBehavior::onLoad()
{
	CombatEvents::TriggerDisableDefend();
}
