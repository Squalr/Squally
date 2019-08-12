#include "EntityEqBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/SaveEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const int EntityEqBehavior::DefaultEq = 1;

EntityEqBehavior* EntityEqBehavior::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntityEqBehavior* instance = new EntityEqBehavior(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntityEqBehavior::EntityEqBehavior(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->eq = EntityEqBehavior::DefaultEq;
	this->eqExperience = 0;
}

EntityEqBehavior::~EntityEqBehavior()
{
}

void EntityEqBehavior::onLoad()
{
}

void EntityEqBehavior::setEq(int eq)
{
	this->eq = eq;
}

int EntityEqBehavior::getEq()
{
	return this->eq;
}

bool EntityEqBehavior::setEqExperience(int eqExperience)
{
	int expToLevel = StatsTables::getExpRequiredAtLevel(this->getEq());

	this->eqExperience = eqExperience;

	if (this->eqExperience >= expToLevel)
	{
		// Level up!
		this->setEq(this->getEq() + 1);
		
		// Recurse to handle potential over-leveling
		this->setEqExperience(this->eqExperience - expToLevel);

		return true;
	}

	return false;
}

bool EntityEqBehavior::addEqExperience(int eqExperience)
{
	return this->setEqExperience(this->getEqExperience() + eqExperience);
}

int EntityEqBehavior::getEqExperience()
{
	return this->eqExperience;
}
