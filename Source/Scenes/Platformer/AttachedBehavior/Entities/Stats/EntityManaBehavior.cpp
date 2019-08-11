#include "EntityManaBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/SaveEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"

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
		this->maxMana = 0;
		this->mana = 0;
		this->invalidate();
	}
	else
	{
		this->maxMana = StatsTables::getBaseMana(this->entity);
		this->mana = this->maxMana;
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
	return this->mana;
}

void EntityManaBehavior::addMana(int manaDelta)
{
	this->setMana(this->getMana() + manaDelta);
}

void EntityManaBehavior::setMana(int mana)
{
	this->mana = MathUtils::clamp(mana, 0, this->getMaxMana());
}

int EntityManaBehavior::getMaxMana()
{
	return this->maxMana;
}

/*
void revive()
{
	this->mana = this->getMaxMana();
}*/
