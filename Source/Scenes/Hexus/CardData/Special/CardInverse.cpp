#include "CardInverse.h"

const std::string CardInverse::StringKeyCardName = "Hexus_Card_Inverse";

CardInverse::CardInverse() : CardData(Resources::Minigames_Hexus_Special_Inverse, CardInverse::StringKeyCardName, CardType::Special_INV, 0)
{
}

CardInverse::~CardInverse()
{
}
