#include "EntityEqBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/SaveEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const int EntityEqBehavior::DefaultEq = 1;

EntityEqBehavior* EntityEqBehavior::create(GameObject* owner)
{
	EntityEqBehavior* instance = new EntityEqBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityEqBehavior::EntityEqBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityEqBehavior::~EntityEqBehavior()
{
}

void EntityEqBehavior::onLoad()
{
}

void EntityEqBehavior::setEq(int eq)
{
	this->entity->setState(StateKeys::Eq, Value(eq), false);
}

int EntityEqBehavior::getEq()
{
	return this->entity->getStateOrDefaultInt(StateKeys::Eq, 0);
}

bool EntityEqBehavior::setEqExperience(int eqExperience)
{
	int expToLevel = StatsTables::getExpRequiredAtLevel(this->getEq());

	this->entity->setState(StateKeys::EqExperience, Value(eqExperience), false);

	if (this->getEqExperience() >= expToLevel)
	{
		// Level up!
		this->setEq(this->getEq() + 1);
		
		// Recurse to handle potential over-leveling
		this->setEqExperience(this->getEqExperience() - expToLevel);

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
	return this->entity->getStateOrDefaultInt(StateKeys::EqExperience, 0);
}
