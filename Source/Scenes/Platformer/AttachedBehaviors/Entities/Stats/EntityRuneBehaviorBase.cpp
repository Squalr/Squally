#include "EntityRuneBehaviorBase.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const int EntityRuneBehaviorBase::MaxRunes = 3;
const float EntityRuneBehaviorBase::RuneCooldown = 24.0f;

EntityRuneBehaviorBase::EntityRuneBehaviorBase(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->entity = static_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->runeCooldowns = std::vector<float>();

	for (int index = 0; index < EntityRuneBehaviorBase::MaxRunes; index++)
	{
		this->runeCooldowns.push_back(0.0f);
	}
}

EntityRuneBehaviorBase::~EntityRuneBehaviorBase()
{
}

void EntityRuneBehaviorBase::onLoad()
{
}

void EntityRuneBehaviorBase::update(float dt)
{
	super::update(dt);

	for (int index = 0; index < this->getMaxRunes(); index++)
	{
		if (this->getRuneCooldown(index) > 0.0f)
		{
			this->setRuneCooldown(index, this->getRuneCooldown(index) - dt);
		}
	}
}

int EntityRuneBehaviorBase::getAvailableRunes()
{
	int availableRunes = 0;

	for (int index = 0; index < this->getMaxRunes(); index++)
	{
		if (this->getRuneCooldown(index) <= 0.0f)
		{
			availableRunes++;
		}
	}

	return availableRunes;
}

bool EntityRuneBehaviorBase::tryUseRune()
{
	for (int index = this->getMaxRunes() - 1; index >= 0; index--)
	{
		if (this->getRuneCooldown(index) <= 0.0f)
		{
			PlatformerEvents::TriggerRuneConsumed(PlatformerEvents::RuneConsumedArgs(this->entity, index));

			this->setRuneCooldown(index, EntityRuneBehaviorBase::RuneCooldown);

			return true;
		}
	}

	return false;
}

float EntityRuneBehaviorBase::getRuneCooldown(int runeIndex)
{
	int index = MathUtils::clamp(runeIndex, 0, this->getMaxRunes() - 1);

	return this->runeCooldowns[index];
}

void EntityRuneBehaviorBase::setRuneCooldown(int runeIndex, float cooldown)
{
	int index = MathUtils::clamp(runeIndex, 0, this->getMaxRunes() - 1);

	this->runeCooldowns[index] = MathUtils::clamp(cooldown, 0.0f, EntityRuneBehaviorBase::RuneCooldown);
}

int EntityRuneBehaviorBase::getMaxRunes()
{
	return EntityRuneBehaviorBase::MaxRunes;
}

// TODO
/*
void onRevive()
{
	for (int index = 0; index < this->getMaxRunes(); index++)
	{
		this->setRuneCooldown(index, 0.0f);
	}
}*/
