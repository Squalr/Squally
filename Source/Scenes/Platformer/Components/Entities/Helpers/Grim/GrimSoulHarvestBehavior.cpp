#include "GrimSoulHarvestBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Events/HelperEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityManaBehavior.h"
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
	this->addEventListener(EventListenerCustom::create(HelperEvents::EventRequestSoulHarvest, [=](EventCustom* eventCustom)
	{
		HelperEvents::RequestSoulHarvestArgs* args = static_cast<HelperEvents::RequestSoulHarvestArgs*>(eventCustom->getData());

		if (args != nullptr && !this->isSoulHarvesting)
		{
			this->trySoulHarvest(args->target, args->onSoulHarvested, args->saveKeySoulHarvested);
		}
	}));

	this->scheduleUpdate();
}

void GrimSoulHarvestBehavior::update(float dt)
{
	super::update(dt);

	if (this->isSoulHarvesting)
	{
		// The target may be moving so keep updating to track it
		this->entity->setState(StateKeys::PatrolDestinationX, Value(GameUtils::getWorldCoords(target).x));
	}
}

void GrimSoulHarvestBehavior::trySoulHarvest(PlatformerEntity* target, std::function<void()> onSoulHarvested, std::string pickPocketSaveKey)
{
	if (this->entity->getRuntimeStateOrDefault(StateKeys::PatrolHijacked, Value(false)).asBool())
	{
		return;
	}
	
	this->isSoulHarvesting = true;
	this->target = target;
	this->entity->setState(StateKeys::PatrolHijacked, Value(true));
	this->entity->setState(StateKeys::PatrolSourceX, Value(GameUtils::getWorldCoords(this->entity).x));
	this->entity->setState(StateKeys::PatrolDestinationX, Value(GameUtils::getWorldCoords(target).x));

	this->entity->listenForStateWriteOnce(StateKeys::PatrolDestinationReached, [=](Value value)
	{
		if (this->isSoulHarvesting)
		{
			this->stopAllActions();
			this->endSoulHarvest();

			int baseHp = StatsTables::getBaseHealth(this->entity);
			int baseMana = StatsTables::getBaseMana(this->entity);

			this->entity->getComponent<EntityHealthBehavior>([&](EntityHealthBehavior* healthBehavior)
			{
				healthBehavior->addHealth(baseHp / 12);
			});

			this->entity->getComponent<EntityManaBehavior>([&](EntityManaBehavior* manaBehavior)
			{
				manaBehavior->addMana(baseMana / 4);
			});

			ObjectEvents::QueryObjects<Squally>([&](Squally* squally)
			{
				squally->getComponent<EntityHealthBehavior>([&](EntityHealthBehavior* healthBehavior)
				{
					healthBehavior->addHealth(baseHp / 2);
				});

				squally->getComponent<EntityManaBehavior>([&](EntityManaBehavior* manaBehavior)
				{
					manaBehavior->addMana(baseMana / 2);
				});
			});

			target->saveObjectState(pickPocketSaveKey, Value(true));

			if (onSoulHarvested != nullptr)
			{
				onSoulHarvested();
			}
		}
	});

	this->runAction(Sequence::create(
		DelayTime::create(5.0f),
		CallFunc::create([=]()
		{
			if (this->isSoulHarvesting)
			{
				this->endSoulHarvest();
			}
		}),
		nullptr
	));
}

void GrimSoulHarvestBehavior::onDisable()
{
	super::onDisable();
}

void GrimSoulHarvestBehavior::endSoulHarvest()
{
	this->isSoulHarvesting = false;
	this->entity->clearState(StateKeys::PatrolHijacked);
	this->entity->clearState(StateKeys::PatrolDestinationX);
	this->entity->runAction(Sequence::create(
		DelayTime::create(1.0f),
		nullptr
	));
}
