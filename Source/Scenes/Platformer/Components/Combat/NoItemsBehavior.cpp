#include "NoItemsBehavior.h"

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
