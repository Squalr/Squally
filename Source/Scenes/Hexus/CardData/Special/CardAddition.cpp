#include "CardAddition.h"

const std::string CardAddition::StringKeyCardName = "Hexus_Card_Addition";

CardAddition::CardAddition() : CardData(Resources::Minigames_Hexus_Special_Addition, CardAddition::StringKeyCardName, CardType::Special_ADD, 0)
{
}

CardAddition::~CardAddition()
{
}
