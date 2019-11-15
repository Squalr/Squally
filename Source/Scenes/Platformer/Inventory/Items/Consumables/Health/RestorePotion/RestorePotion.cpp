#include "RestorePotion.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/RestorePotion/ThrowRestorePotion.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Consumables/Health/RestorePotion.h"

using namespace cocos2d;

const std::string RestorePotion::SaveKeyRestorePotion = "restore-potion";

RestorePotion* RestorePotion::create()
{
	RestorePotion* instance = new RestorePotion();

	instance->autorelease();

	return instance;
}

RestorePotion::RestorePotion() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
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
