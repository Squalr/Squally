#include "EntityRuneBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const int EntityRuneBehavior::MaxRunes = 3;
const float EntityRuneBehavior::RuneCooldown = 2.0f;

EntityRuneBehavior* EntityRuneBehavior::create(GameObject* owner)
{
	EntityRuneBehavior* instance = new EntityRuneBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityRuneBehavior::EntityRuneBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->runeCooldowns = std::vector<float>();

	for (int index = 0; index < EntityRuneBehavior::MaxRunes; index++)
	{
		this->runeCooldowns.push_back(0.0f);
	}
}

EntityRuneBehavior::~EntityRuneBehavior()
{
}

void EntityRuneBehavior::onLoad()
{
	if (this->entity != nullptr)
	{
		this->entity->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
		{
			if (value.asBool())
			{
				this->onRevive();
			}
		});
	}
}

void EntityRuneBehavior::onDisable()
{
	super::onDisable();
}

void EntityRuneBehavior::update(float dt)
{
	super::update(dt);

	for (int index = 0; index < EntityRuneBehavior::MaxRunes; index++)
	{
		if (this->getRuneCooldown(index) > 0.0f)
		{
			this->setRuneCooldown(index, this->getRuneCooldown(index) - dt);
		}
	}
}

int EntityRuneBehavior::getAvailableRunes()
{
	int availableRunes = 0;

	for (int index = 0; index < EntityRuneBehavior::MaxRunes; index++)
	{
		if (this->getRuneCooldown(index) <= 0.0f)
		{
			availableRunes++;
		}
	}

	return availableRunes;
}

bool EntityRuneBehavior::tryUseRune()
{
	for (int index = EntityRuneBehavior::MaxRunes - 1; index >= 0; index--)
	{
		if (this->getRuneCooldown(index) <= 0.0f)
		{
			PlatformerEvents::TriggerRuneConsumed(PlatformerEvents::RuneConsumedArgs(this->entity, index));

			this->setRuneCooldown(index, EntityRuneBehavior::RuneCooldown);

			return true;
		}
	}

	return false;
}

float EntityRuneBehavior::getRuneCooldown(int runeIndex)
{
	int index = MathUtils::clamp(runeIndex, 0, EntityRuneBehavior::MaxRunes - 1);

	return this->runeCooldowns[index];
}

void EntityRuneBehavior::setRuneCooldown(int runeIndex, float cooldown)
{
	int index = MathUtils::clamp(runeIndex, 0, EntityRuneBehavior::MaxRunes - 1);

	this->runeCooldowns[index] = MathUtils::clamp(cooldown, 0.0f, EntityRuneBehavior::RuneCooldown);
}

void EntityRuneBehavior::onRevive()
{
	for (int index = 0; index < EntityRuneBehavior::MaxRunes; index++)
	{
		this->setRuneCooldown(index, 0.0f);
	}
}
