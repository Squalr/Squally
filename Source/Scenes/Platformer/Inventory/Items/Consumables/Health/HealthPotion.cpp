#include "HealthPotion.h"

#include "Scenes/Platformer/Level/Combat/Attacks/Consumables/Health/ThrowHealthPotion.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Consumables/Health/HealthPotion.h"

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
	this->associatedAttack = ThrowHealthPotion::create();

	this->addChild(this->associatedAttack);
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
	return Strings::Items_Consumables_Health_HealthPotion::create();
}

std::string HealthPotion::getIconResource()
{
	return ObjectResources::Items_Consumables_HEALTH_2;
}

std::string HealthPotion::getSerializationKey()
{
	return HealthPotion::SaveKeyHealthPotion;
}

Consumable::ConsumableType HealthPotion::getConsumableType()
{
	return ConsumableType::Buff;
}
