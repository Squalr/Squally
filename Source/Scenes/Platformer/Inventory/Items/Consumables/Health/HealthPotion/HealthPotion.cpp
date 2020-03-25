#include "HealthPotion.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/HealthPotion/ThrowHealthPotion.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HealthPotion::SaveKey = "health-potion";
const float HealthPotion::HealPercentage = 0.4f;

HealthPotion* HealthPotion::create()
{
	HealthPotion* instance = new HealthPotion();

	instance->autorelease();

	return instance;
}

HealthPotion::HealthPotion() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 14 }}), ItemMeta(20, RubberBanding(3, 0.15f)))
{
}

HealthPotion::~HealthPotion()
{
}

Item* HealthPotion::clone()
{
	return HealthPotion::create();
}

std::string HealthPotion::getItemName()
{
	return HealthPotion::SaveKey;
}

LocalizedString* HealthPotion::getString()
{
	return Strings::Items_Consumables_Health_HealthPotion::create();
}

std::string HealthPotion::getIconResource()
{
	return ItemResources::Consumables_Potions_HealthPotion;
}

std::string HealthPotion::getSerializationKey()
{
	return HealthPotion::SaveKey;
}

PlatformerAttack* HealthPotion::createAssociatedAttack()
{
	return ThrowHealthPotion::create(PlatformerAttack::Priority::Common, HealthPotion::HealPercentage, this->getIconResource());
}
