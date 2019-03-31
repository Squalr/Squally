#include "CardResurrect.h"

#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/HexusResources.h"

CardResurrect::CardResurrect() : CardData(HexusResources::Special_ResurrectionStone, CardKeys::Resurrect, CardType::Special_RESURRECT, 0)
{
}

CardResurrect::~CardResurrect()
{
}
