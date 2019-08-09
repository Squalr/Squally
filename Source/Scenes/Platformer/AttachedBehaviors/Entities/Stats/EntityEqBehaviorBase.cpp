#include "EntityEqBehaviorBase.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/SaveEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const int EntityEqBehaviorBase::DefaultEq = 1;

EntityEqBehaviorBase::EntityEqBehaviorBase(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->entity = static_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->eq = EntityEqBehaviorBase::DefaultEq;
	this->eqExperience = 0;
}

EntityEqBehaviorBase::~EntityEqBehaviorBase()
{
}

void EntityEqBehaviorBase::onLoad()
{
}

void EntityEqBehaviorBase::setEq(int eq)
{
	this->eq = eq;
}

int EntityEqBehaviorBase::getEq()
{
	return this->eq;
}

bool EntityEqBehaviorBase::setEqExperience(int eqExperience)
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

bool EntityEqBehaviorBase::addEqExperience(int eqExperience)
{
	return this->setEqExperience(this->getEqExperience() + eqExperience);
}

int EntityEqBehaviorBase::getEqExperience()
{
	return this->eqExperience;
}
