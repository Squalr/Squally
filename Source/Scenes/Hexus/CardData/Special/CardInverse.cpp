#include "CardInverse.h"

#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/HexusResources.h"

CardInverse::CardInverse() : CardData(HexusResources::Special_Inverse, CardKeys::Inverse, CardType::Special_NOT, 0)
{
}

CardInverse::~CardInverse()
{
}
