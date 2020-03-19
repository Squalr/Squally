#include "ManaPotion.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Mana/ManaPotion/ThrowManaPotion.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ManaPotion::SaveKey = "mana-potion";
const float ManaPotion::RestorePercentage = 0.4f;

ManaPotion* ManaPotion::create()
{
	ManaPotion* instance = new ManaPotion();

	instance->autorelease();

	return instance;
}

ManaPotion::ManaPotion() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 17 }}), ItemMeta(20, RubberBanding(3, 0.15f)))
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
	return ManaPotion::SaveKey;
}

LocalizedString* ManaPotion::getString()
{
	return Strings::Items_Consumables_Mana_ManaPotion::create();
}

std::string ManaPotion::getIconResource()
{
	return ItemResources::Consumables_Potions_ManaPotion;
}

std::string ManaPotion::getSerializationKey()
{
	return ManaPotion::SaveKey;
}

PlatformerAttack* ManaPotion::createAssociatedAttack()
{
	return ThrowManaPotion::create();
}
