#include "CardKill.h"

#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/HexusResources.h"

CardKill::CardKill() : CardData(HexusResources::Special_Kill, CardKeys::Kill, CardType::Special_KILL, 0)
{
}

CardKill::~CardKill()
{
}
