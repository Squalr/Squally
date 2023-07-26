#include "EntityBuffBehavior.h"

#include <algorithm>
#include <iterator>
#include <set>

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
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
	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventBuffRemoved, [=](EventCustom* eventCustom)
	{
		CombatEvents::BuffRemovedArgs* args = static_cast<CombatEvents::BuffRemovedArgs*>(eventCustom->getData());

		if (args != nullptr && std::find(this->buffs.begin(), this->buffs.end(), args->buff) != this->buffs.end())
		{
			this->buffsToRemove.push_back(args->buff);
		}
	}));

	this->entity->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (!value.asBool())
		{
			this->removeAllBuffs();
		}
	});
	
	this->setPosition(this->entity->getEntityCenterPoint());
	this->scheduleUpdate();
}

void EntityBuffBehavior::update(float dt)
{
	super::update(dt);

	for (Buff* next : this->buffsToRemove)
	{
		this->removeBuff(next);
	}

	this->buffsToRemove.clear();
}

void EntityBuffBehavior::onDisable()
{
	super::onDisable();
}

void EntityBuffBehavior::sortBuffs()
{
	std::sort(this->buffs.begin(), this->buffs.end(), 
		[](Buff* a, Buff* b)
	{ 
		return a->getBuffData().priority > b->getBuffData().priority; 
	});
}

std::vector<Buff*> EntityBuffBehavior::getBuffs()
{
	// Clone is ideal, callers will often call functions that will result in this list changing
	return std::vector<Buff*>(this->buffs);
}

void EntityBuffBehavior::applyBuff(Buff* buff, bool checkAlive)
{
	if (this->entity == nullptr || buff == nullptr)
	{
		return;
	}

	if (checkAlive && !this->entity->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
	{
		return;
	}

	if (!buff->getBuffData().uniqueId.empty())
	{
		this->removeBuffsById(buff->getBuffData().uniqueId);
	}
	
	this->buffs.push_back(buff);
	this->buffNode->addChild(buff);

	this->sortBuffs();
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

	this->sortBuffs();
	this->repositionBuffIcons();
}

void EntityBuffBehavior::removeBuffsById(std::string buffId)
{
	std::vector<Buff*> buffsCopy = this->buffs;

	for (Buff* buff : buffsCopy)
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
	std::set<Buff*> buffsSet = std::set<Buff*>(this->buffs.begin(), this->buffs.end());
	std::set<Buff*> removedBuffs = std::set<Buff*>();

	for (Buff* next : buffsSet)
	{
		if (next->removeBuff())
		{
			removedBuffs.insert(next);
			this->buffNode->removeChild(next);
		}
	}

	// Retain any buffs that could not be removed
	this->buffs.clear();
	std::set_difference(
		buffsSet.begin(), buffsSet.end(),
		removedBuffs.begin(), removedBuffs.end(),
		std::back_inserter(this->buffs)
	);
}

void EntityBuffBehavior::repositionBuffIcons()
{
	int maxIndex = -1;

	for (Buff* next : this->buffs)
	{
		if (next->hasBuffIcon())
		{
			maxIndex++;
		}
	}

	int adjustedIndex = 0;

	for (Buff* next : this->buffs)
	{
		if (next->hasBuffIcon())
		{
			next->setBuffIndex(adjustedIndex++, maxIndex);
		}
	}
}
