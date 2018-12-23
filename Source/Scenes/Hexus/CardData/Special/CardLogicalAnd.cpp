#include "CardLogicalAnd.h"

#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/HexusResources.h"

CardLogicalAnd::CardLogicalAnd() : CardData(HexusResources::Special_LogicalAnd, CardKeys::LogicalAnd, CardType::Special_AND, 0)
{
}

CardLogicalAnd::~CardLogicalAnd()
{
}
