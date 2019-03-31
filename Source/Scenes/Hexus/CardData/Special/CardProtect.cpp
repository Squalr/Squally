#include "CardProtect.h"

#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/HexusResources.h"

CardProtect::CardProtect() : CardData(HexusResources::Special_Protect, CardKeys::Protect, CardType::Special_PROTECT, 0)
{
}

CardProtect::~CardProtect()
{
}
