#include "GreaterHealthPotion.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/HealthPotion/ThrowHealthPotion.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GreaterHealthPotion::SaveKey = "greater-health-potion";
const float GreaterHealthPotion::HealPercentage = 0.4f;

GreaterHealthPotion* GreaterHealthPotion::create()
{
	GreaterHealthPotion* instance = new GreaterHealthPotion();

	instance->autorelease();

	return instance;
}

// Note: No rubber-banding, as these are to be considered a rare item
GreaterHealthPotion::GreaterHealthPotion() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 27 }}), ItemMeta(20))
{
}

GreaterHealthPotion::~GreaterHealthPotion()
{
}

Item* GreaterHealthPotion::clone()
{
	return GreaterHealthPotion::create();
}

std::string GreaterHealthPotion::getItemName()
{
	return GreaterHealthPotion::SaveKey;
}

LocalizedString* GreaterHealthPotion::getString()
{
	return Strings::Items_Consumables_Health_GreaterHealthPotion::create();
}

std::string GreaterHealthPotion::getIconResource()
{
	return ItemResources::Consumables_Potions_HealthPotionGreater;
}

std::string GreaterHealthPotion::getSerializationKey()
{
	return GreaterHealthPotion::SaveKey;
}

PlatformerAttack* GreaterHealthPotion::createAssociatedAttack()
{
	return ThrowHealthPotion::create(PlatformerAttack::Priority::Common, GreaterHealthPotion::HealPercentage, this->getIconResource());
}
