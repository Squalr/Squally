#include "CardGreed.h"

#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/HexusResources.h"

CardGreed::CardGreed() : CardData(HexusResources::Special_Greed, CardKeys::Greed, CardType::Special_GREED, 0)
{
}

CardGreed::~CardGreed()
{
}
