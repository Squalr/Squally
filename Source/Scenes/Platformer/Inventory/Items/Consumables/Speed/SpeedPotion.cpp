#include "SpeedPotion.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string SpeedPotion::SaveKeySpeedPotion = "speed-potion";

SpeedPotion* SpeedPotion::create()
{
	SpeedPotion* instance = new SpeedPotion();

	instance->autorelease();

	return instance;
}

SpeedPotion::SpeedPotion() : Consumable()
{
}

SpeedPotion::~SpeedPotion()
{
}

Item* SpeedPotion::clone()
{
	return SpeedPotion::create();
}

LocalizedString* SpeedPotion::getString()
{
	return nullptr;
}

std::string SpeedPotion::getIconResource()
{
	return ObjectResources::Items_Consumables_YELLOW_RUNE;
}

std::string SpeedPotion::getSerializationKey()
{
	return SpeedPotion::SaveKeySpeedPotion;
}

PlatformerAttack* SpeedPotion::getAssociatedAttack()
{
	return nullptr;
}

Consumable::ConsumableType SpeedPotion::getConsumableType()
{
	return ConsumableType::Buff;
}
