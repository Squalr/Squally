#include "CopperHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CopperHelm::SaveKeyCopperHelm = "copper-helm";

CopperHelm* CopperHelm::create()
{
	CopperHelm* instance = new CopperHelm();

	instance->autorelease();

	return instance;
}

CopperHelm::CopperHelm() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

CopperHelm::~CopperHelm()
{
}

Item* CopperHelm::clone()
{
	return CopperHelm::create();
}

std::string CopperHelm::getItemName()
{
	return CopperHelm::SaveKeyCopperHelm;
}

LocalizedString* CopperHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

std::string CopperHelm::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_CopperHelm;
}

std::string CopperHelm::getSerializationKey()
{
	return CopperHelm::SaveKeyCopperHelm;
}

Vec2 CopperHelm::getDisplayOffset()
{
	return Vec2(12.0f, -24.0f);
}
