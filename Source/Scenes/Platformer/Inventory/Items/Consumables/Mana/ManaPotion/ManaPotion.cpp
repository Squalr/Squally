#include "ManaPotion.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/RestorePotion/ThrowRestorePotion.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ManaPotion::SaveKeyManaPotion = "mana-potion";

ManaPotion* ManaPotion::create()
{
	ManaPotion* instance = new ManaPotion();

	instance->autorelease();

	return instance;
}

ManaPotion::ManaPotion() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(20, RubberBanding(3, 0.15f)))
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

LocalizedString* ManaPotion::getString()
{
	return Strings::Items_Consumables_Mana_ManaPotion::create();
}

std::string ManaPotion::getIconResource()
{
	return ObjectResources::Items_Consumables_Potions_MANA_5;
}

std::string ManaPotion::getSerializationKey()
{
	return ManaPotion::SaveKeyManaPotion;
}

PlatformerAttack* ManaPotion::createAssociatedAttack()
{
	return ThrowRestorePotion::create();
}
