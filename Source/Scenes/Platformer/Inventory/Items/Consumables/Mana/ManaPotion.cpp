#include "ManaPotion.h"

#include "Scenes/Platformer/Level/Combat/Attacks/Consumables/Health/ThrowHealthPotion.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Consumables/Mana/ManaPotion.h"

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

std::string ManaPotion::getItemName()
{
	return ManaPotion::SaveKeyManaPotion;
}

PlatformerAttack* ManaPotion::createAssociatedAttack()
{
	return ThrowHealthPotion::create();
}

LocalizedString* ManaPotion::getString()
{
	return Strings::Items_Consumables_Mana_ManaPotion::create();
}

std::string ManaPotion::getIconResource()
{
	return ObjectResources::Items_Consumables_MANA_5;
}

std::string ManaPotion::getSerializationKey()
{
	return ManaPotion::SaveKeyManaPotion;
}

Consumable::ConsumableType ManaPotion::getConsumableType()
{
	return ConsumableType::Buff;
}
