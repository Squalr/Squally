#include "EntityBuffBehavior.h"

#include "cocos/base/CCValue.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Level/Combat/Buffs/Buff.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityBuffBehavior::MapKey = "entity-buff";

EntityBuffBehavior* EntityBuffBehavior::create(GameObject* owner)
{
	EntityBuffBehavior* instance = new EntityBuffBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityBuffBehavior::EntityBuffBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->buffs = std::vector<Buff*>();
	this->buffNode = Node::create();

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->buffNode);
}

EntityBuffBehavior::~EntityBuffBehavior()
{
}

void EntityBuffBehavior::onLoad()
{
	this->entity->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (!value.asBool())
		{
			this->removeAllBuffs();
		}
	});
	
	this->setPosition(this->entity->getEntityCenterPoint());
}

void EntityBuffBehavior::onDisable()
{
	super::onDisable();
}

void EntityBuffBehavior::applyBuff(Buff* buff)
{
	if (this->entity == nullptr || buff == nullptr)
	{
		return;
	}

	if (!this->entity->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
	{
		return;
	}

	if (!buff->getBuffData().uniqueId.empty())
	{
		this->removeBuffsById(buff->getBuffData().uniqueId);
	}
	
	buff->setRemoveBuffCallback([=]() { this->removeBuff(buff); });
	this->buffs.push_back(buff);
	this->buffNode->addChild(buff);

	this->repositionBuffIcons();

	CombatEvents::TriggerBuffApplied(CombatEvents::BuffAppliedArgs(this->entity, buff));
}

void EntityBuffBehavior::removeBuff(Buff* buff)
{
	if (buff == nullptr)
	{
		return;
	}

	if (std::find(this->buffs.begin(), this->buffs.end(), buff) != this->buffs.end())
	{
		this->buffs.erase(std::remove(this->buffs.begin(), this->buffs.end(), buff), this->buffs.end());
		this->buffNode->removeChild(buff);
	}

	this->repositionBuffIcons();
}

void EntityBuffBehavior::removeBuffsById(std::string buffId)
{
	std::vector<Buff*> buffsCopy = this->buffs;

	for (auto buff : buffsCopy)
	{
		if (buff == nullptr)
		{
			continue;
		}

		if (buff->getBuffData().uniqueId == buffId)
		{
			this->removeBuff(buff);
		}
	}
}

void EntityBuffBehavior::removeAllBuffs()
{
	std::vector<Buff*> buffsCopy = this->buffs;

	for (auto next : buffsCopy)
	{
		next->removeBuff();
	}

	// Shouldnt be needed, added as safety
	this->buffs.clear();
	this->buffNode->removeAllChildren();
}

void EntityBuffBehavior::repositionBuffIcons()
{
	int maxIndex = -1;
	
	for (auto next : this->buffs)
	{
		if (next->hasBuffIcon())
		{
			maxIndex++;
		}
	}

	for (int index = 0; index < int(this->buffs.size()); index++)
	{
		if (this->buffs[index]->hasBuffIcon())
		{
			this->buffs[index]->setBuffIndex(index, maxIndex);
		}
	}
}
