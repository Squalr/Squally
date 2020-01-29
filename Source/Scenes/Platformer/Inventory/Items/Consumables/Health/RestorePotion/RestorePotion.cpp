#include "RestorePotion.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/RestorePotion/ThrowRestorePotion.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RestorePotion::SaveKeyRestorePotion = "restore-potion";
const int RestorePotion::HealTicks = 8;

RestorePotion* RestorePotion::create()
{
	RestorePotion* instance = new RestorePotion();

	instance->autorelease();

	return instance;
}

RestorePotion::RestorePotion() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20, RubberBanding(3, 0.15f)))
{
}

RestorePotion::~RestorePotion()
{
}

Item* RestorePotion::clone()
{
	return RestorePotion::create();
}

std::string RestorePotion::getItemName()
{
	return RestorePotion::SaveKeyRestorePotion;
}

LocalizedString* RestorePotion::getString()
{
	return Strings::Items_Consumables_Health_RestorePotion::create();
}

std::string RestorePotion::getIconResource()
{
	return ObjectResources::Items_Consumables_Potions_HEALTH_2;
}

std::string RestorePotion::getSerializationKey()
{
	return RestorePotion::SaveKeyRestorePotion;
}

PlatformerAttack* RestorePotion::createAssociatedAttack()
{
	return ThrowRestorePotion::create();
}
