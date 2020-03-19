#include "NoItemsBehavior.h"

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

const std::string NoItemsBehavior::MapKey = "no-items";

NoItemsBehavior* NoItemsBehavior::create(GameObject* owner)
{
	NoItemsBehavior* instance = new NoItemsBehavior(owner);

	instance->autorelease();

	return instance;
}

NoItemsBehavior::NoItemsBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

NoItemsBehavior::~NoItemsBehavior()
{
}

void NoItemsBehavior::onLoad()
{
	CombatEvents::TriggerDisableItems();
}

void NoItemsBehavior::onDisable()
{
	super::onDisable();
}
