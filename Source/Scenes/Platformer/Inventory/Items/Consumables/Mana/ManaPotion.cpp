#include "ManaPotion.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string ManaPotion::SaveKeyManaPotion = "mana-potion";

ManaPotion* ManaPotion::create()
{
	ManaPotion* instance = new ManaPotion();

	instance->autorelease();

	return instance;
}

ManaPotion::ManaPotion() : Consumable()
{
}

ManaPotion::~ManaPotion()
{
}

Item* ManaPotion::clone()
{
	return ManaPotion::create();
}

LocalizedString* ManaPotion::getString()
{
	return nullptr;
}

std::string ManaPotion::getIconResource()
{
	return ObjectResources::Items_Consumables_MANA_5;
}

std::string ManaPotion::getSerializationKey()
{
	return ManaPotion::SaveKeyManaPotion;
}

PlatformerAttack* ManaPotion::getAssociatedAttack()
{
	return nullptr;
}

Consumable::ConsumableType ManaPotion::getConsumableType()
{
	return ConsumableType::Buff;
}
