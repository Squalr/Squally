#include "CardPeek.h"

#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/HexusResources.h"

CardPeek::CardPeek() : CardData(HexusResources::Special_Peek, CardKeys::Peek, CardType::Special_PEEK, 0)
{
}

CardPeek::~CardPeek()
{
}
