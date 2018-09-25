#include "CardLogicalOr.h"

const std::string CardLogicalOr::StringKeyCardName = "Hexus_Card_Logical_Or";

CardLogicalOr::CardLogicalOr() : CardData(Resources::Minigames_Hexus_Special_LogicalOr, CardLogicalOr::StringKeyCardName, CardType::Special_OR, 0)
{
}

CardLogicalOr::~CardLogicalOr()
{
}
