#pragma init_seg(".CRT$XCU-020")
#include "CardData.h"

const std::string CardData::Binary0 = "Pebble";
const std::string CardData::Binary1 = "Peanut";
const std::string CardData::Binary2 = "Skitters";
const std::string CardData::Binary3 = "Shroomy";
const std::string CardData::Binary4 = "Stabby";
const std::string CardData::Binary5 = "Stabby II";
const std::string CardData::Binary6 = "M-Bot";
const std::string CardData::Binary7 = "N.E.P.T.U.N.E";
const std::string CardData::Binary8 = "Crush-o-matic";
const std::string CardData::Binary9 = "Magma Golem";
const std::string CardData::Binary10 = "Mantis";
const std::string CardData::Binary11 = "Rock Golem";
const std::string CardData::Binary12 = "Tree Spirit";
const std::string CardData::Binary13 = "Gem Golem";
const std::string CardData::Binary14 = "Yeti";
const std::string CardData::Binary15 = "Metal Golem";
const std::string CardData::Decimal0 = "Carrot";
const std::string CardData::Decimal1 = "Jess";
const std::string CardData::Decimal2 = "Fisherman";
const std::string CardData::Decimal3 = "Maurader";
const std::string CardData::Decimal4 = "Iden";
const std::string CardData::Decimal5 = "Caine 'One Eye' Thorn";
const std::string CardData::Decimal6 = "Kovius";
const std::string CardData::Decimal7 = "Jax";
const std::string CardData::Decimal8 = "Powerfox";
const std::string CardData::Decimal9 = "Aiden";
const std::string CardData::Decimal10 = "Irrius";
const std::string CardData::Decimal11 = "Klide";
const std::string CardData::Decimal12 = "Zatrax";
const std::string CardData::Decimal13 = "Getic the Insane";
const std::string CardData::Decimal14 = "Berserker";
const std::string CardData::Decimal15 = "The Keeper";
const std::string CardData::Hex0 = "Demon Haunch";
const std::string CardData::Hex1 = "Gweeb";
const std::string CardData::Hex2 = "Blat";
const std::string CardData::Hex3 = "Jacob";
const std::string CardData::Hex4 = "Gnip";
const std::string CardData::Hex5 = "Spooks";
const std::string CardData::Hex6 = "Doob";
const std::string CardData::Hex7 = "Sp00ks";
const std::string CardData::Hex8 = "Mother";
const std::string CardData::Hex9 = "Hydra";
const std::string CardData::Hex10 = "Carl";
const std::string CardData::Hex11 = "Shaman";
const std::string CardData::Hex12 = "Captain Sp00ks";
const std::string CardData::Hex13 = "King Sp00ks";
const std::string CardData::Hex14 = "Goliath";
const std::string CardData::Hex15 = "Xarth";
const std::string CardData::BinaryAddition = "Binary Addition";
const std::string CardData::BinarySubtraction = "Binary Subtraction";
const std::string CardData::Flip1 = "Flip Bit 1";
const std::string CardData::Flip2 = "Flip Bit 2";
const std::string CardData::Flip3 = "Flip Bit 3";
const std::string CardData::Flip4 = "Flip Bit 4";
const std::string CardData::LogicalAnd = "Logical AND";
const std::string CardData::LogicalOr = "Logical OR";
const std::string CardData::LogicalXor = "Logical XOR";
const std::string CardData::ShiftLeft = "Shift Left";
const std::string CardData::ShiftRight = "Shift Right";
const std::string CardData::BitFlip = "Bit Flip";
const std::string CardData::Clear = "Clear";
const std::string CardData::Greed = "Draw 2";
const std::string CardData::Peek = "Peek";

std::map<std::string, CardData*> CardData::cardListByName = {
	{ CardData::Binary0, new CardData(Resources::Minigames_Hexium_Binary_0, CardData::Binary0, CardType::Binary) },
	{ CardData::Binary1, new CardData(Resources::Minigames_Hexium_Binary_1, CardData::Binary1, CardType::Binary) },
	{ CardData::Binary2, new CardData(Resources::Minigames_Hexium_Binary_2, CardData::Binary2, CardType::Binary) },
	{ CardData::Binary3, new CardData(Resources::Minigames_Hexium_Binary_3, CardData::Binary3, CardType::Binary) },
	{ CardData::Binary4, new CardData(Resources::Minigames_Hexium_Binary_4, CardData::Binary4, CardType::Binary) },
	{ CardData::Binary5, new CardData(Resources::Minigames_Hexium_Binary_5, CardData::Binary5, CardType::Binary) },
	{ CardData::Binary6, new CardData(Resources::Minigames_Hexium_Binary_6, CardData::Binary6, CardType::Binary) },
	{ CardData::Binary7, new CardData(Resources::Minigames_Hexium_Binary_7, CardData::Binary7, CardType::Binary) },
	{ CardData::Binary8, new CardData(Resources::Minigames_Hexium_Binary_8, CardData::Binary8, CardType::Binary) },
	{ CardData::Binary9, new CardData(Resources::Minigames_Hexium_Binary_9, CardData::Binary9, CardType::Binary) },
	{ CardData::Binary10, new CardData(Resources::Minigames_Hexium_Binary_10, CardData::Binary10, CardType::Binary) },
	{ CardData::Binary11, new CardData(Resources::Minigames_Hexium_Binary_11, CardData::Binary11, CardType::Binary) },
	{ CardData::Binary12, new CardData(Resources::Minigames_Hexium_Binary_12, CardData::Binary12, CardType::Binary) },
	{ CardData::Binary13, new CardData(Resources::Minigames_Hexium_Binary_13, CardData::Binary13, CardType::Binary) },
	{ CardData::Binary14, new CardData(Resources::Minigames_Hexium_Binary_14, CardData::Binary14, CardType::Binary) },
	{ CardData::Binary15, new CardData(Resources::Minigames_Hexium_Binary_15, CardData::Binary15, CardType::Binary) },
	{ CardData::Decimal0, new CardData(Resources::Minigames_Hexium_Decimal_0, CardData::Decimal0, CardType::Decimal) },
	{ CardData::Decimal1, new CardData(Resources::Minigames_Hexium_Decimal_1, CardData::Decimal1, CardType::Decimal) },
	{ CardData::Decimal2, new CardData(Resources::Minigames_Hexium_Decimal_2, CardData::Decimal2, CardType::Decimal) },
	{ CardData::Decimal3, new CardData(Resources::Minigames_Hexium_Decimal_3, CardData::Decimal3, CardType::Decimal) },
	{ CardData::Decimal4, new CardData(Resources::Minigames_Hexium_Decimal_4, CardData::Decimal4, CardType::Decimal) },
	{ CardData::Decimal5, new CardData(Resources::Minigames_Hexium_Decimal_5, CardData::Decimal5, CardType::Decimal) },
	{ CardData::Decimal6, new CardData(Resources::Minigames_Hexium_Decimal_6, CardData::Decimal6, CardType::Decimal) },
	{ CardData::Decimal7, new CardData(Resources::Minigames_Hexium_Decimal_7, CardData::Decimal7, CardType::Decimal) },
	{ CardData::Decimal8, new CardData(Resources::Minigames_Hexium_Decimal_8, CardData::Decimal8, CardType::Decimal) },
	{ CardData::Decimal9, new CardData(Resources::Minigames_Hexium_Decimal_9, CardData::Decimal9, CardType::Decimal) },
	{ CardData::Decimal10, new CardData(Resources::Minigames_Hexium_Decimal_10, CardData::Decimal10, CardType::Decimal) },
	{ CardData::Decimal11, new CardData(Resources::Minigames_Hexium_Decimal_11, CardData::Decimal11, CardType::Decimal) },
	{ CardData::Decimal12, new CardData(Resources::Minigames_Hexium_Decimal_12, CardData::Decimal12, CardType::Decimal) },
	{ CardData::Decimal13, new CardData(Resources::Minigames_Hexium_Decimal_13, CardData::Decimal13, CardType::Decimal) },
	{ CardData::Decimal14, new CardData(Resources::Minigames_Hexium_Decimal_14, CardData::Decimal14, CardType::Decimal) },
	{ CardData::Decimal15, new CardData(Resources::Minigames_Hexium_Decimal_15, CardData::Decimal15, CardType::Decimal) },
	{ CardData::Hex0, new CardData(Resources::Minigames_Hexium_Hex_0, CardData::Hex0, CardType::Decimal) },
	{ CardData::Hex1, new CardData(Resources::Minigames_Hexium_Hex_1, CardData::Hex1, CardType::Decimal) },
	{ CardData::Hex2, new CardData(Resources::Minigames_Hexium_Hex_2, CardData::Hex2, CardType::Decimal) },
	{ CardData::Hex3, new CardData(Resources::Minigames_Hexium_Hex_3, CardData::Hex3, CardType::Decimal) },
	{ CardData::Hex4, new CardData(Resources::Minigames_Hexium_Hex_4, CardData::Hex4, CardType::Decimal) },
	{ CardData::Hex5, new CardData(Resources::Minigames_Hexium_Hex_5, CardData::Hex5, CardType::Decimal) },
	{ CardData::Hex6, new CardData(Resources::Minigames_Hexium_Hex_6, CardData::Hex6, CardType::Decimal) },
	{ CardData::Hex7, new CardData(Resources::Minigames_Hexium_Hex_7, CardData::Hex7, CardType::Decimal) },
	{ CardData::Hex8, new CardData(Resources::Minigames_Hexium_Hex_8, CardData::Hex8, CardType::Decimal) },
	{ CardData::Hex9, new CardData(Resources::Minigames_Hexium_Hex_9, CardData::Hex9, CardType::Decimal) },
	{ CardData::Hex10, new CardData(Resources::Minigames_Hexium_Hex_10, CardData::Hex10, CardType::Decimal) },
	{ CardData::Hex11, new CardData(Resources::Minigames_Hexium_Hex_11, CardData::Hex11, CardType::Decimal) },
	{ CardData::Hex12, new CardData(Resources::Minigames_Hexium_Hex_12, CardData::Hex12, CardType::Decimal) },
	{ CardData::Hex13, new CardData(Resources::Minigames_Hexium_Hex_13, CardData::Hex13, CardType::Decimal) },
	{ CardData::Hex14, new CardData(Resources::Minigames_Hexium_Hex_14, CardData::Hex14, CardType::Decimal) },
	{ CardData::Hex15, new CardData(Resources::Minigames_Hexium_Hex_15, CardData::Hex15, CardType::Decimal) },
	{ CardData::BinaryAddition, new CardData(Resources::Minigames_Hexium_Special_BinaryAddition, CardData::BinaryAddition, CardType::Special) },
	{ CardData::BinarySubtraction, new CardData(Resources::Minigames_Hexium_Special_BinarySubtraction, CardData::BinarySubtraction, CardType::Special) },
	{ CardData::Flip1, new CardData(Resources::Minigames_Hexium_Special_Flip1, CardData::Flip1, CardType::Special) },
	{ CardData::Flip2, new CardData(Resources::Minigames_Hexium_Special_Flip2, CardData::Flip2, CardType::Special) },
	{ CardData::Flip3, new CardData(Resources::Minigames_Hexium_Special_Flip3, CardData::Flip3, CardType::Special) },
	{ CardData::Flip4, new CardData(Resources::Minigames_Hexium_Special_Flip4, CardData::Flip4, CardType::Special) },
	{ CardData::LogicalAnd, new CardData(Resources::Minigames_Hexium_Special_LogicalAnd, CardData::LogicalAnd, CardType::Special) },
	{ CardData::LogicalOr, new CardData(Resources::Minigames_Hexium_Special_LogicalOr, CardData::LogicalOr, CardType::Special) },
	{ CardData::LogicalXor, new CardData(Resources::Minigames_Hexium_Special_LogicalXor, CardData::LogicalXor, CardType::Special) },
	{ CardData::ShiftLeft, new CardData(Resources::Minigames_Hexium_Special_ShiftLeft, CardData::ShiftLeft, CardType::Special) },
	{ CardData::ShiftRight, new CardData(Resources::Minigames_Hexium_Special_ShiftRight, CardData::ShiftRight, CardType::Special) },
	{ CardData::BitFlip, new CardData(Resources::Minigames_Hexium_Special_BitFlip, CardData::BitFlip, CardType::Special) },
	{ CardData::Clear, new CardData(Resources::Minigames_Hexium_Special_Clear , CardData::Clear, CardType::Special) },
	{ CardData::Greed, new CardData(Resources::Minigames_Hexium_Special_Greed, CardData::Greed, CardType::Special) },
	{ CardData::Peek, new CardData(Resources::Minigames_Hexium_Special_Peek, CardData::Peek, CardType::Special) },
};

// Use a map here instead of an array. This allows us to remove cards without fucking up the ids of other cards.
// ie) The case of putting out a steam patch to remove a broken card without ruining existing save files.

std::map<int, CardData*> CardData::cardListById = {
	{ 0, CardData::cardListByName.at(CardData::Binary0) },
	{ 1, CardData::cardListByName.at(CardData::Binary1) },
	{ 2, CardData::cardListByName.at(CardData::Binary2) },
	{ 2, CardData::cardListByName.at(CardData::Binary3) },
	{ 3, CardData::cardListByName.at(CardData::Binary4) },
	{ 4, CardData::cardListByName.at(CardData::Binary5) },
	{ 5, CardData::cardListByName.at(CardData::Binary6) },
	{ 6, CardData::cardListByName.at(CardData::Binary7) },
	{ 7, CardData::cardListByName.at(CardData::Binary8) },
	{ 8, CardData::cardListByName.at(CardData::Binary9) },
	{ 9, CardData::cardListByName.at(CardData::Binary10) },
	{ 10, CardData::cardListByName.at(CardData::Binary11) },
	{ 11, CardData::cardListByName.at(CardData::Binary12) },
	{ 12, CardData::cardListByName.at(CardData::Binary13) },
	{ 13, CardData::cardListByName.at(CardData::Binary14) },
	{ 14, CardData::cardListByName.at(CardData::Binary15) },
	{ 15, CardData::cardListByName.at(CardData::Decimal0) },
	{ 16, CardData::cardListByName.at(CardData::Decimal1) },
	{ 17, CardData::cardListByName.at(CardData::Decimal2) },
	{ 18, CardData::cardListByName.at(CardData::Decimal3) },
	{ 19, CardData::cardListByName.at(CardData::Decimal4) },
	{ 20, CardData::cardListByName.at(CardData::Decimal5) },
	{ 21, CardData::cardListByName.at(CardData::Decimal6) },
	{ 22, CardData::cardListByName.at(CardData::Decimal7) },
	{ 23, CardData::cardListByName.at(CardData::Decimal8) },
	{ 24, CardData::cardListByName.at(CardData::Decimal9) },
	{ 25, CardData::cardListByName.at(CardData::Decimal10) },
	{ 26, CardData::cardListByName.at(CardData::Decimal11) },
	{ 27, CardData::cardListByName.at(CardData::Decimal12) },
	{ 28, CardData::cardListByName.at(CardData::Decimal13) },
	{ 29, CardData::cardListByName.at(CardData::Decimal14) },
	{ 30, CardData::cardListByName.at(CardData::Decimal15) },
	{ 31, CardData::cardListByName.at(CardData::Hex0) },
	{ 32, CardData::cardListByName.at(CardData::Hex1) },
	{ 33, CardData::cardListByName.at(CardData::Hex2) },
	{ 34, CardData::cardListByName.at(CardData::Hex3) },
	{ 35, CardData::cardListByName.at(CardData::Hex4) },
	{ 36, CardData::cardListByName.at(CardData::Hex5) },
	{ 37, CardData::cardListByName.at(CardData::Hex6) },
	{ 38, CardData::cardListByName.at(CardData::Hex7) },
	{ 39, CardData::cardListByName.at(CardData::Hex8) },
	{ 40, CardData::cardListByName.at(CardData::Hex9) },
	{ 41, CardData::cardListByName.at(CardData::Hex10) },
	{ 42, CardData::cardListByName.at(CardData::Hex11) },
	{ 43, CardData::cardListByName.at(CardData::Hex12) },
	{ 44, CardData::cardListByName.at(CardData::Hex13) },
	{ 45, CardData::cardListByName.at(CardData::Hex14) },
	{ 46, CardData::cardListByName.at(CardData::Hex15) },
	{ 47, CardData::cardListByName.at(CardData::BinaryAddition) },
	{ 48, CardData::cardListByName.at(CardData::BinarySubtraction) },
	{ 49, CardData::cardListByName.at(CardData::Flip1) },
	{ 50, CardData::cardListByName.at(CardData::Flip2) },
	{ 51, CardData::cardListByName.at(CardData::Flip3) },
	{ 52, CardData::cardListByName.at(CardData::Flip4) },
	{ 53, CardData::cardListByName.at(CardData::LogicalAnd) },
	{ 54, CardData::cardListByName.at(CardData::LogicalOr) },
	{ 55, CardData::cardListByName.at(CardData::LogicalXor) },
	{ 56, CardData::cardListByName.at(CardData::ShiftLeft) },
	{ 57, CardData::cardListByName.at(CardData::ShiftRight) },
	{ 58, CardData::cardListByName.at(CardData::BitFlip) },
	{ 59, CardData::cardListByName.at(CardData::Clear) },
	{ 60, CardData::cardListByName.at(CardData::Greed) },
	{ 61, CardData::cardListByName.at(CardData::Peek) },
};

CardData::CardData(std::string newCardResourceFile, std::string newCardName, CardType newCardType)
{
	this->cardResourceFile = newCardResourceFile;
	this->cardName = newCardName;
	this->cardType = newCardType;
}

CardData::~CardData()
{
}
