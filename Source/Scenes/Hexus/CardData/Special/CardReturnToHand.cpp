#include "CardReturnToHand.h"

#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/HexusResources.h"

CardReturnToHand::CardReturnToHand() : CardData(HexusResources::Special_ReturnToHand, CardKeys::ReturnToHand, CardType::Special_RETURN_TO_HAND, 0)
{
}

CardReturnToHand::~CardReturnToHand()
{
}
