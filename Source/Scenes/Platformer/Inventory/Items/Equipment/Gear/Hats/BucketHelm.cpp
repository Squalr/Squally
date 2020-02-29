#include "BucketHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BucketHelm::SaveKeyBucketHelm = "bucket-helm";

BucketHelm* BucketHelm::create()
{
	BucketHelm* instance = new BucketHelm();

	instance->autorelease();

	return instance;
}

BucketHelm::BucketHelm() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

BucketHelm::~BucketHelm()
{
}

Item* BucketHelm::clone()
{
	return BucketHelm::create();
}

std::string BucketHelm::getItemName()
{
	return BucketHelm::SaveKeyBucketHelm;
}

LocalizedString* BucketHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_BucketHelm::create();
}

std::string BucketHelm::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_BucketHelm;
}

std::string BucketHelm::getSerializationKey()
{
	return BucketHelm::SaveKeyBucketHelm;
}

Vec2 BucketHelm::getDisplayOffset()
{
	return Vec2(6.0f, -20.0f);
}
