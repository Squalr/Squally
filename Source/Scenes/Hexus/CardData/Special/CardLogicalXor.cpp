#include "CardLogicalXor.h"

const std::string CardLogicalXor::StringKeyCardName = "Hexus_Card_Logical_Xor";

CardLogicalXor::CardLogicalXor() : CardData(Resources::Minigames_Hexus_Special_LogicalXor, CardLogicalXor::StringKeyCardName, CardType::Special_XOR, 0)
{
}

CardLogicalXor::~CardLogicalXor()
{
}
