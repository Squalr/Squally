#include "EntityBuffBehavior.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityBuffBehavior::MapKeyAttachedBehavior = "entity-buff";

EntityBuffBehavior* EntityBuffBehavior::create(GameObject* owner)
{
	EntityBuffBehavior* instance = new EntityBuffBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityBuffBehavior::EntityBuffBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityBuffBehavior::~EntityBuffBehavior()
{
}

void EntityBuffBehavior::applyBuff(Buff* buff)
{
	this->addChild(buff);

	CombatEvents::TriggerBuffApplied(CombatEvents::BuffAppliedArgs(this->entity, buff));
}

void EntityBuffBehavior::onLoad()
{
}
