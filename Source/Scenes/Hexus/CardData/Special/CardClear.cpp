#include "CardClear.h"

#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/HexusResources.h"

CardClear::CardClear() : CardData(HexusResources::Special_Clear, CardKeys::Clear, CardType::Special_CLEAR, 0)
{
}

CardClear::~CardClear()
{
}
