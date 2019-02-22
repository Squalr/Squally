#include "HealthPotion.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

HealthPotion* HealthPotion::create()
{
	HealthPotion* instance = new HealthPotion();

	instance->autorelease();

	return instance;
}

HealthPotion::HealthPotion() : Consumable(nullptr, ObjectResources::Items_Consumables_HEALTH_1)
{
}

HealthPotion::~HealthPotion()
{
}
