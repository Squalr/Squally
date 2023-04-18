#include "GrimSoulHarvestBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/HelperEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GrimSoulHarvestBehavior::MapKey = "soul-harvester";

GrimSoulHarvestBehavior* GrimSoulHarvestBehavior::create(GameObject* owner)
{
	GrimSoulHarvestBehavior* instance = new GrimSoulHarvestBehavior(owner);

	instance->autorelease();

	return instance;
}

GrimSoulHarvestBehavior::GrimSoulHarvestBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

GrimSoulHarvestBehavior::~GrimSoulHarvestBehavior()
{
}

void GrimSoulHarvestBehavior::onLoad()
{
	this->addEventListener(EventListenerCustom::create(HelperEvents::EventRequestPickPocket, [=](EventCustom* eventCustom)
	{
		HelperEvents::RequestPickPocketArgs* args = static_cast<HelperEvents::RequestPickPocketArgs*>(eventCustom->getData());

		if (args != nullptr && !this->isPickPocketing)
		{
			this->tryPickPocket(args->target, args->pocketPool, args->onPickPocket, args->saveKeyPickPocketed);
		}
	}));

	this->scheduleUpdate();
}

void GrimSoulHarvestBehavior::update(float dt)
{
	super::update(dt);

	if (this->isPickPocketing)
	{
		// The target may be moving so keep updating to track it
		this->entity->setState(StateKeys::PatrolDestinationX, Value(GameUtils::getWorldCoords(target).x));
	}
}

void GrimSoulHarvestBehavior::tryPickPocket(PlatformerEntity* target, MinMaxPool* pocketPool, std::function<void()> onPickPocket, std::string pickPocketSaveKey)
{
	if (pocketPool == nullptr)
	{
		return;
	}

	if (this->entity->getRuntimeStateOrDefault(StateKeys::PatrolHijacked, Value(false)).asBool())
	{
		return;
	}
	
	this->isPickPocketing = true;
	this->target = target;
	this->entity->setState(StateKeys::PatrolHijacked, Value(true));
	this->entity->setState(StateKeys::PatrolSourceX, Value(GameUtils::getWorldCoords(this->entity).x));
	this->entity->setState(StateKeys::PatrolDestinationX, Value(GameUtils::getWorldCoords(target).x));
	this->entity->setOpacity(192);

	this->entity->listenForStateWriteOnce(StateKeys::PatrolDestinationReached, [=](Value value)
	{
		if (this->isPickPocketing)
		{
			this->stopAllActions();
			this->endPickPocket();

			PlatformerEvents::TriggerGiveItemsFromPool(PlatformerEvents::GiveItemsFromPoolArgs(pocketPool));

			target->saveObjectState(pickPocketSaveKey, Value(true));

			if (onPickPocket != nullptr)
			{
				onPickPocket();
			}
		}
	});

	this->runAction(Sequence::create(
		DelayTime::create(5.0f),
		CallFunc::create([=]()
		{
			if (this->isPickPocketing)
			{
				this->endPickPocket();
			}
		}),
		nullptr
	));
}

void GrimSoulHarvestBehavior::onDisable()
{
	super::onDisable();
}

void GrimSoulHarvestBehavior::endPickPocket()
{
	this->isPickPocketing = false;
	this->entity->clearState(StateKeys::PatrolHijacked);
	this->entity->clearState(StateKeys::PatrolDestinationX);
	this->entity->runAction(Sequence::create(
		DelayTime::create(1.0f),
		FadeTo::create(0.25f, 255),
		nullptr
	));
}
