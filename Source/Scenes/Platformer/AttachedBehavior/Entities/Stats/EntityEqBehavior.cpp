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
	this->saveKeyEq = "";
	this->saveKeyExp = "";

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

void EntityEqBehavior::onDisable()
{
	super::onDisable();
}

void EntityEqBehavior::load(std::string saveKeyEq, std::string saveKeyExp)
{
	this->saveKeyEq = saveKeyEq;
	this->saveKeyExp = saveKeyExp;

	int eq = SaveManager::getProfileDataOrDefault(this->saveKeyEq, Value(1)).asInt();
	int exp = SaveManager::getProfileDataOrDefault(this->saveKeyExp, Value(0)).asInt();

	this->entity->setState(StateKeys::Eq, Value(eq), false);
	this->entity->setState(StateKeys::EqExperience, Value(exp), false);
}

void EntityEqBehavior::setEq(int eq)
{
	this->entity->setState(StateKeys::Eq, Value(eq), false);

	this->save();
}

int EntityEqBehavior::getEq()
{
	return this->entity->getRuntimeStateOrDefaultInt(StateKeys::Eq, 1);
}

bool EntityEqBehavior::setEqExperience(int eqExperience)
{
	int expToLevel = StatsTables::getExpRequiredAtLevel(this->entity);

	this->entity->setState(StateKeys::EqExperience, Value(eqExperience), false);

	if (this->getEqExperience() >= expToLevel)
	{
		// Level up!
		this->setEq(this->getEq() + 1);
		
		// Recurse to handle potential over-leveling
		this->setEqExperience(this->getEqExperience() - expToLevel);

		return true;
	}

	this->save();

	return false;
}

bool EntityEqBehavior::addEqExperience(int eqExperience)
{
	return this->setEqExperience(this->getEqExperience() + eqExperience);
}

int EntityEqBehavior::getEqExperience()
{
	return this->entity->getRuntimeStateOrDefaultInt(StateKeys::EqExperience, 0);
}

void EntityEqBehavior::save()
{
	if (this->saveKeyEq.empty() || this->saveKeyExp.empty())
	{
		return;
	}

	SaveManager::SoftSaveProfileData(this->saveKeyEq, Value(this->getEq()));
	SaveManager::SoftSaveProfileData(this->saveKeyExp, Value(this->getEqExperience()));
}
