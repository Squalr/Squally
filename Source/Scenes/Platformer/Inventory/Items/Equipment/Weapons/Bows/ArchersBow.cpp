#include "ArchersBow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ArchersBow::SaveKeyArchersBow = "archers-bow";

ArchersBow* ArchersBow::create()
{
	ArchersBow* instance = new ArchersBow();

	instance->autorelease();

	return instance;
}

ArchersBow::ArchersBow() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

ArchersBow::~ArchersBow()
{
}

Item* ArchersBow::clone()
{
	return ArchersBow::create();
}

std::string ArchersBow::getItemName()
{
	return ArchersBow::SaveKeyArchersBow;
}

LocalizedString* ArchersBow::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_ArchersBow::create();
}

std::string ArchersBow::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Bows_ArchersBow;
}

std::string ArchersBow::getSerializationKey()
{
	return ArchersBow::SaveKeyArchersBow;
}

Vec2 ArchersBow::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
