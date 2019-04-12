#include "CardSteal.h"

#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/HexusResources.h"

CardSteal::CardSteal() : CardData(HexusResources::Special_Steal, CardKeys::Steal, CardType::Special_STEAL, 0)
{
}

CardSteal::~CardSteal()
{
}
