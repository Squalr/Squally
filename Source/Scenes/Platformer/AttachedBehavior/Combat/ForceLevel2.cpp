#include "ForceLevel2.h"

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

const std::string ForceLevel2::MapKeyAttachedBehavior = "force-level-2";

ForceLevel2* ForceLevel2::create(GameObject* owner)
{
	ForceLevel2* instance = new ForceLevel2(owner);

	instance->autorelease();

	return instance;
}

ForceLevel2::ForceLevel2(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

ForceLevel2::~ForceLevel2()
{
}

void ForceLevel2::onLoad()
{
	CombatEvents::TriggerDisableDefend();
}
