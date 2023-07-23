#include "KillingMachineHealthBehavior.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/SaveEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Scenes/Platformer/Level/Huds/Components/StatsBars.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string KillingMachineHealthBehavior::MapKey = "killing-machine-health";

KillingMachineHealthBehavior* KillingMachineHealthBehavior::create(GameObject* owner)
{
	KillingMachineHealthBehavior* instance = new KillingMachineHealthBehavior(owner);

	instance->autorelease();

	return instance;
}

KillingMachineHealthBehavior::KillingMachineHealthBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEnemy*>(owner);
	this->statsBars = StatsBars::create(true, false);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->statsBars);
}

KillingMachineHealthBehavior::~KillingMachineHealthBehavior()
{
}

void KillingMachineHealthBehavior::onLoad()
{
	super::onLoad();

	this->statsBars->setPosition(Vec2(-192.0f, 420.0f));
	this->statsBars->disableInteraction(0);
	this->statsBars->toggleManaBarVisibility(false);
	this->statsBars->toggleEmblemVisibility(false);
	this->statsBars->setStatsTarget(this->entity);

	this->entity->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (!value.asBool())
		{
			this->entity->runAction(Sequence::create(
				DelayTime::create(1.0f),
				FadeTo::create(1.0f, 0),
				nullptr
			));
			this->entity->despawn(2.5f);
		}
	});
}

void KillingMachineHealthBehavior::onDisable()
{
	super::onDisable();
}
