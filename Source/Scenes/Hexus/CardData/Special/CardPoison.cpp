#include "CardPoison.h"

#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/HexusResources.h"

CardPoison::CardPoison() : CardData(HexusResources::Special_Poison, CardKeys::Poison, CardType::Special_POISON, 0)
{
}

CardPoison::~CardPoison()
{
}
