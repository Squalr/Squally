#include "CardPush.h"

#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/HexusResources.h"

CardPush::CardPush() : CardData(HexusResources::Special_Push, CardKeys::Push, CardType::Special_PUSH, 0)
{
}

CardPush::~CardPush()
{
}
