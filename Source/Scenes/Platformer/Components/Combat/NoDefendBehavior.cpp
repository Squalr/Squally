#include "NoDefendBehavior.h"

#include "2d/CCActionEase.h"
#include "2d/CCActionInstant.h"
#include "2d/CCActionInterval.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCValue.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

const std::string NoDefendBehavior::MapKey = "no-defend";

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

void NoDefendBehavior::onDisable()
{
	super::onDisable();
}
