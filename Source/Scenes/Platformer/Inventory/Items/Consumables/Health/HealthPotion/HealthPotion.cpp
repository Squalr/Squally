#include "HealthPotion.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/HealthPotion/ThrowHealthPotion.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HealthPotion::SaveKeyHealthPotion = "health-potion";

HealthPotion* HealthPotion::create()
{
	HealthPotion* instance = new HealthPotion();

	instance->autorelease();

	return instance;
}

HealthPotion::HealthPotion() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(3, 0.15f))
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
	return HealthPotion::SaveKeyHealthPotion;
}

LocalizedString* HealthPotion::getString()
{
	return Strings::Items_Consumables_Health_HealthPotion::create();
}

std::string HealthPotion::getIconResource()
{
	return ObjectResources::Items_Consumables_Potions_HEALTH_2;
}

std::string HealthPotion::getSerializationKey()
{
	return HealthPotion::SaveKeyHealthPotion;
}

PlatformerAttack* HealthPotion::createAssociatedAttack()
{
	return ThrowHealthPotion::create();
}
