#include "EntityManaBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/SaveEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

EntityManaBehavior* EntityManaBehavior::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntityManaBehavior* instance = new EntityManaBehavior(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntityManaBehavior::EntityManaBehavior(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->entity = static_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->entity->setState(StateKeys::MaxMana, Value(StatsTables::getBaseMana(this->entity)), false);
		this->entity->setState(StateKeys::Mana, Value(StatsTables::getBaseMana(this->entity)), false);
	}
}

EntityManaBehavior::~EntityManaBehavior()
{
}

void EntityManaBehavior::onLoad()
{
}

int EntityManaBehavior::getMana()
{
	return this->entity->getStateOrDefaultInt(StateKeys::Mana, 0);
}

void EntityManaBehavior::addMana(int manaDelta)
{
	this->setMana(this->getMana() + manaDelta);
}

void EntityManaBehavior::setMana(int mana)
{
	mana = MathUtils::clamp(mana, 0, this->entity->getStateOrDefaultInt(StateKeys::MaxMana, 0));
	this->entity->setState(StateKeys::Mana, Value(mana), false);
}

int EntityManaBehavior::getMaxMana()
{
	return this->entity->getStateOrDefaultInt(StateKeys::MaxMana, 0);
}
