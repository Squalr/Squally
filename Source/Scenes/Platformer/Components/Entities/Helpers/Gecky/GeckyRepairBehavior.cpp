#include "GeckyRepairBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Sound/Sound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/HelperEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/InteractObject.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GeckyRepairBehavior::MapKey = "repairer";

GeckyRepairBehavior* GeckyRepairBehavior::create(GameObject* owner)
{
	GeckyRepairBehavior* instance = new GeckyRepairBehavior(owner);

	instance->autorelease();

	return instance;
}

GeckyRepairBehavior::GeckyRepairBehavior(GameObject* owner) : super(owner)
{
	this->sound = Sound::create(SoundResources::Notifications_NotificationGood1);
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->sound);
}

GeckyRepairBehavior::~GeckyRepairBehavior()
{
}

void GeckyRepairBehavior::onLoad()
{
	this->addEventListener(EventListenerCustom::create(HelperEvents::EventRequestRepair, [=](EventCustom* eventCustom)
	{
		HelperEvents::RequestRepairArgs* args = static_cast<HelperEvents::RequestRepairArgs*>(eventCustom->getData());

		if (args != nullptr && !this->isRepairing)
		{
			this->tryRepair(args->target, args->onRepaired, args->repairEvent, args->saveKeyRepaired);
		}
	}));

	this->scheduleUpdate();
}

void GeckyRepairBehavior::update(float dt)
{
	super::update(dt);

	if (this->isRepairing)
	{
		// The target may be moving so keep updating to track it
		this->entity->setState(StateKeys::PatrolDestinationX, Value(GameUtils::getWorldCoords(target).x));
	}
}

void GeckyRepairBehavior::tryRepair(InteractObject* target, std::function<void()> onRepaired, std::string repairEvent, std::string repairSaveKey)
{
	if (this->entity->getRuntimeStateOrDefault(StateKeys::PatrolHijacked, Value(false)).asBool())
	{
		return;
	}
	
	this->isRepairing = true;
	this->target = target;
	this->entity->setState(StateKeys::PatrolHijacked, Value(true));
	this->entity->setState(StateKeys::PatrolSourceX, Value(GameUtils::getWorldCoords(this->entity).x));
	this->entity->setState(StateKeys::PatrolDestinationX, Value(GameUtils::getWorldCoords(this->target).x));

	this->entity->listenForStateWriteOnce(StateKeys::PatrolDestinationReached, [=](Value value)
	{
		if (this->isRepairing)
		{
			this->stopAllActions();
			this->endRepair();

			ObjectEvents::TriggerBroadCastMapObjectState(repairEvent, ValueMap());
			this->target->saveObjectState(repairSaveKey, Value(true));
			this->target->unlock(true);
			this->sound->play();

			if (onRepaired != nullptr)
			{
				onRepaired();
			}
		}
	});

	this->runAction(Sequence::create(
		DelayTime::create(5.0f),
		CallFunc::create([=]()
		{
			if (this->isRepairing)
			{
				this->endRepair();
			}
		}),
		nullptr
	));
}

void GeckyRepairBehavior::onDisable()
{
	super::onDisable();
}

void GeckyRepairBehavior::endRepair()
{
	this->isRepairing = false;
	this->entity->clearState(StateKeys::PatrolHijacked);
	this->entity->clearState(StateKeys::PatrolDestinationX);
	this->entity->runAction(Sequence::create(
		DelayTime::create(1.0f),
		FadeTo::create(0.25f, 255),
		nullptr
	));
}
