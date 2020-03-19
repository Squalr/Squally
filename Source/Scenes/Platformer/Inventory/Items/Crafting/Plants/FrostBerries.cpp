#include "FrostBerries.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FrostBerries::SaveKey = "frost-berries";

FrostBerries* FrostBerries::create()
{
	FrostBerries* instance = new FrostBerries();

	instance->autorelease();

	return instance;
}

FrostBerries::FrostBerries() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 36 }}), ItemMeta(20000))
{
}

FrostBerries::~FrostBerries()
{
}

Item* FrostBerries::clone()
{
	return FrostBerries::create();
}

std::string FrostBerries::getItemName()
{
	return FrostBerries::SaveKey;
}

LocalizedString* FrostBerries::getString()
{
	return Strings::Items_Crafting_Plants_FrostBerries::create();
}

std::string FrostBerries::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Plants_FrostBerries;
}

std::string FrostBerries::getSerializationKey()
{
	return FrostBerries::SaveKey;
}
