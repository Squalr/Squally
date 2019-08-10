#include "EntityManaBehaviorBase.h"

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

EntityManaBehaviorBase::EntityManaBehaviorBase(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
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

EntityManaBehaviorBase::~EntityManaBehaviorBase()
{
}

void EntityManaBehaviorBase::onLoad()
{
}

int EntityManaBehaviorBase::getMana()
{
	return this->mana;
}

void EntityManaBehaviorBase::addMana(int manaDelta)
{
	this->setMana(this->getMana() + manaDelta);
}

void EntityManaBehaviorBase::setMana(int mana)
{
	this->mana = MathUtils::clamp(mana, 0, this->getMaxMana());
}

int EntityManaBehaviorBase::getMaxMana()
{
	return this->maxMana;
}

/*
void revive()
{
	this->mana = this->getMaxMana();
}*/
