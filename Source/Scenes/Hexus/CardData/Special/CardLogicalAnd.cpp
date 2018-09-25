#include "CardLogicalAnd.h"

const std::string CardLogicalAnd::StringKeyCardName = "Hexus_Card_Logical_And";

CardLogicalAnd::CardLogicalAnd() : CardData(Resources::Minigames_Hexus_Special_LogicalAnd, CardLogicalAnd::StringKeyCardName, CardType::Special_AND, 0)
{
}

CardLogicalAnd::~CardLogicalAnd()
{
}
