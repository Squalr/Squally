#include "HealthPotion.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string HealthPotion::SaveKeyHealthPotion = "health-potion";

HealthPotion* HealthPotion::create()
{
	HealthPotion* instance = new HealthPotion();

	instance->autorelease();

	return instance;
}

HealthPotion::HealthPotion() : Consumable()
{
}

HealthPotion::~HealthPotion()
{
}

Item* HealthPotion::clone()
{
	return HealthPotion::create();
}

LocalizedString* HealthPotion::getString()
{
	return nullptr;
}

std::string HealthPotion::getIconResource()
{
	return ObjectResources::Items_Consumables_HEALTH_2;
}

std::string HealthPotion::getSerializationKey()
{
	return HealthPotion::SaveKeyHealthPotion;
}

PlatformerAttack* HealthPotion::getAssociatedAttack()
{
	return nullptr;
}

Consumable::ConsumableType HealthPotion::getConsumableType()
{
	return ConsumableType::Buff;
}
