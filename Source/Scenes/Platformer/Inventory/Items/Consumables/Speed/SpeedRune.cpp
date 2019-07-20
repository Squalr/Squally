#include "SpeedRune.h"

#include "Scenes/Platformer/Level/Combat/Attacks/Consumables/Speed/ThrowSpeedRune.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Consumables/Speed/SpeedRune.h"

using namespace cocos2d;

const std::string SpeedRune::SaveKeySpeedRune = "speed-rune";

SpeedRune* SpeedRune::create()
{
	SpeedRune* instance = new SpeedRune();

	instance->autorelease();

	return instance;
}

SpeedRune::SpeedRune() : Consumable()
{
}

SpeedRune::~SpeedRune()
{
}

Item* SpeedRune::clone()
{
	return SpeedRune::create();
}

std::string SpeedRune::getItemName()
{
	return SpeedRune::SaveKeySpeedRune;
}

PlatformerAttack* SpeedRune::createAssociatedAttack()
{
	return ThrowSpeedRune::create();
}

LocalizedString* SpeedRune::getString()
{
	return Strings::Items_Consumables_Speed_SpeedRune::create();
}

std::string SpeedRune::getIconResource()
{
	return ObjectResources::Items_Consumables_YELLOW_RUNE;
}

std::string SpeedRune::getSerializationKey()
{
	return SpeedRune::SaveKeySpeedRune;
}

Consumable::ConsumableType SpeedRune::getConsumableType()
{
	return ConsumableType::Buff;
}
