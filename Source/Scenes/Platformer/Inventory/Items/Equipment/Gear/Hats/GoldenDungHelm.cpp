#include "GoldenDungHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoldenDungHelm::SaveKeyGoldenDungHelm = "golden-dung-helm";

GoldenDungHelm* GoldenDungHelm::create()
{
	GoldenDungHelm* instance = new GoldenDungHelm();

	instance->autorelease();

	return instance;
}

GoldenDungHelm::GoldenDungHelm() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

GoldenDungHelm::~GoldenDungHelm()
{
}

Item* GoldenDungHelm::clone()
{
	return GoldenDungHelm::create();
}

std::string GoldenDungHelm::getItemName()
{
	return GoldenDungHelm::SaveKeyGoldenDungHelm;
}

LocalizedString* GoldenDungHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

std::string GoldenDungHelm::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_GoldenDungHelm;
}

std::string GoldenDungHelm::getSerializationKey()
{
	return GoldenDungHelm::SaveKeyGoldenDungHelm;
}

Vec2 GoldenDungHelm::getDisplayOffset()
{
	return Vec2(12.0f, -24.0f);
}
