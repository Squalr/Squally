#include "Harbinger.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Swords/Harbinger.h"

using namespace cocos2d;

const std::string Harbinger::SaveKeyHarbinger = "harbinger";

Harbinger* Harbinger::create()
{
	Harbinger* instance = new Harbinger();

	instance->autorelease();

	return instance;
}

Harbinger::Harbinger() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

Harbinger::~Harbinger()
{
}

Item* Harbinger::clone()
{
	return Harbinger::create();
}

std::string Harbinger::getItemName()
{
	return Harbinger::SaveKeyHarbinger;
}

LocalizedString* Harbinger::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_Harbinger::create();
}

std::string Harbinger::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_Harbinger;
}

std::string Harbinger::getSerializationKey()
{
	return Harbinger::SaveKeyHarbinger;
}
