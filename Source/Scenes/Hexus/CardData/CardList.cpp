#include "CardList.h"

CardList* CardList::instance = nullptr;

// Internal use only. Save files will key against these names -- do not change them after release
const std::string CardList::Binary0 = "Binary_0";
const std::string CardList::Binary1 = "Binary_1";
const std::string CardList::Binary2 = "Binary_2";
const std::string CardList::Binary3 = "Binary_3";
const std::string CardList::Binary4 = "Binary_4";
const std::string CardList::Binary5 = "Binary_5";
const std::string CardList::Binary6 = "Binary_6";
const std::string CardList::Binary7 = "Binary_7";
const std::string CardList::Binary8 = "Binary_8";
const std::string CardList::Binary9 = "Binary_9";
const std::string CardList::Binary10 = "Binary_10";
const std::string CardList::Binary11 = "Binary_11";
const std::string CardList::Binary12 = "Binary_12";
const std::string CardList::Binary13 = "Binary_13";
const std::string CardList::Binary14 = "Binary_14";
const std::string CardList::Binary15 = "Binary_15";
const std::string CardList::Decimal0 = "Decimal_0";
const std::string CardList::Decimal1 = "Decimal_1";
const std::string CardList::Decimal2 = "Decimal_2";
const std::string CardList::Decimal3 = "Decimal_3";
const std::string CardList::Decimal4 = "Decimal_4";
const std::string CardList::Decimal5 = "Decimal_5";
const std::string CardList::Decimal6 = "Decimal_6";
const std::string CardList::Decimal7 = "Decimal_7";
const std::string CardList::Decimal8 = "Decimal_8";
const std::string CardList::Decimal9 = "Decimal_9";
const std::string CardList::Decimal10 = "Decimal_10";
const std::string CardList::Decimal11 = "Decimal_11";
const std::string CardList::Decimal12 = "Decimal_12";
const std::string CardList::Decimal13 = "Decimal_13";
const std::string CardList::Decimal14 = "Decimal_14";
const std::string CardList::Decimal15 = "Decimal_15";
const std::string CardList::Hex0 = "Hex_0";
const std::string CardList::Hex1 = "Hex_1";
const std::string CardList::Hex2 = "Hex_2";
const std::string CardList::Hex3 = "Hex_3";
const std::string CardList::Hex4 = "Hex_4";
const std::string CardList::Hex5 = "Hex_5";
const std::string CardList::Hex6 = "Hex_6";
const std::string CardList::Hex7 = "Hex_7";
const std::string CardList::Hex8 = "Hex_8";
const std::string CardList::Hex9 = "Hex_9";
const std::string CardList::Hex10 = "Hex_10";
const std::string CardList::Hex11 = "Hex_11";
const std::string CardList::Hex12 = "Hex_12";
const std::string CardList::Hex13 = "Hex_13";
const std::string CardList::Hex14 = "Hex_14";
const std::string CardList::Hex15 = "Hex_15";
const std::string CardList::Addition = "Addition";
const std::string CardList::EnvironmentBinStorm = "Environment_Bin_Storm";
const std::string CardList::EnvironmentClear = "Environment_Clear";
const std::string CardList::EnvironmentDecStorm = "Environment_Dec_Storm";
const std::string CardList::EnvironmentHexStorm = "Environment_Hex_Storm";
const std::string CardList::Flip1 = "Flip_1";
const std::string CardList::Flip2 = "Flip_2";
const std::string CardList::Flip3 = "Flip_3";
const std::string CardList::Flip4 = "Flip_4";
const std::string CardList::Inverse = "Inverse";
const std::string CardList::LogicalAnd = "Logical_AND";
const std::string CardList::LogicalOr = "Logical_OR";
const std::string CardList::LogicalXor = "Logical_XOR";
const std::string CardList::ShiftLeft = "Shift_Left";
const std::string CardList::ShiftRight = "Shift_Right";
const std::string CardList::Subtraction = "Subtraction";

CardList* CardList::getInstance()
{
	if (CardList::instance == nullptr)
	{
		CardList::instance = new CardList();
	}

	return CardList::instance;
}

CardList::CardList()
{
	this->cardListByName = new std::map<std::string, CardData*>();

	this->cardListByName->emplace(CardList::Binary0, new CardBinary0());
	this->cardListByName->emplace(CardList::Binary1, new CardBinary1());
	this->cardListByName->emplace(CardList::Binary2, new CardBinary2());
	this->cardListByName->emplace(CardList::Binary3, new CardBinary3());
	this->cardListByName->emplace(CardList::Binary4, new CardBinary4());
	this->cardListByName->emplace(CardList::Binary5, new CardBinary5());
	this->cardListByName->emplace(CardList::Binary6, new CardBinary6());
	this->cardListByName->emplace(CardList::Binary7, new CardBinary7());
	this->cardListByName->emplace(CardList::Binary8, new CardBinary8());
	this->cardListByName->emplace(CardList::Binary9, new CardBinary9());
	this->cardListByName->emplace(CardList::Binary10, new CardBinary10());
	this->cardListByName->emplace(CardList::Binary11, new CardBinary11());
	this->cardListByName->emplace(CardList::Binary12, new CardBinary12());
	this->cardListByName->emplace(CardList::Binary13, new CardBinary13());
	this->cardListByName->emplace(CardList::Binary14, new CardBinary14());
	this->cardListByName->emplace(CardList::Binary15, new CardBinary15());
	this->cardListByName->emplace(CardList::Binary15, new CardBinary15());

	this->cardListByName->emplace(CardList::Decimal0, new CardDecimal0());
	this->cardListByName->emplace(CardList::Decimal1, new CardDecimal1());
	this->cardListByName->emplace(CardList::Decimal2, new CardDecimal2());
	this->cardListByName->emplace(CardList::Decimal3, new CardDecimal3());
	this->cardListByName->emplace(CardList::Decimal4, new CardDecimal4());
	this->cardListByName->emplace(CardList::Decimal5, new CardDecimal5());
	this->cardListByName->emplace(CardList::Decimal6, new CardDecimal6());
	this->cardListByName->emplace(CardList::Decimal7, new CardDecimal7());
	this->cardListByName->emplace(CardList::Decimal8, new CardDecimal8());
	this->cardListByName->emplace(CardList::Decimal9, new CardDecimal9());
	this->cardListByName->emplace(CardList::Decimal10, new CardDecimal10());
	this->cardListByName->emplace(CardList::Decimal11, new CardDecimal11());
	this->cardListByName->emplace(CardList::Decimal12, new CardDecimal12());
	this->cardListByName->emplace(CardList::Decimal13, new CardDecimal13());
	this->cardListByName->emplace(CardList::Decimal14, new CardDecimal14());
	this->cardListByName->emplace(CardList::Decimal15, new CardDecimal15());

	this->cardListByName->emplace(CardList::Hex0, new CardHex0());
	this->cardListByName->emplace(CardList::Hex1, new CardHex1());
	this->cardListByName->emplace(CardList::Hex2, new CardHex2());
	this->cardListByName->emplace(CardList::Hex3, new CardHex3());
	this->cardListByName->emplace(CardList::Hex4, new CardHex4());
	this->cardListByName->emplace(CardList::Hex5, new CardHex5());
	this->cardListByName->emplace(CardList::Hex6, new CardHex6());
	this->cardListByName->emplace(CardList::Hex7, new CardHex7());
	this->cardListByName->emplace(CardList::Hex8, new CardHex8());
	this->cardListByName->emplace(CardList::Hex9, new CardHex9());
	this->cardListByName->emplace(CardList::Hex10, new CardHex10());
	this->cardListByName->emplace(CardList::Hex11, new CardHex11());
	this->cardListByName->emplace(CardList::Hex12, new CardHex12());
	this->cardListByName->emplace(CardList::Hex13, new CardHex13());
	this->cardListByName->emplace(CardList::Hex14, new CardHex14());
	this->cardListByName->emplace(CardList::Hex15, new CardHex15());

	this->cardListByName->emplace(CardList::Addition, new CardAddition());
	this->cardListByName->emplace(CardList::Flip1, new CardFlip1());
	this->cardListByName->emplace(CardList::Flip2, new CardFlip2());
	this->cardListByName->emplace(CardList::Flip3, new CardFlip3());
	this->cardListByName->emplace(CardList::Flip4, new CardFlip4());
	this->cardListByName->emplace(CardList::Inverse, new CardInverse());
	this->cardListByName->emplace(CardList::LogicalAnd, new CardLogicalAnd());
	this->cardListByName->emplace(CardList::LogicalOr, new CardLogicalOr());
	this->cardListByName->emplace(CardList::LogicalXor, new CardLogicalXor());
	this->cardListByName->emplace(CardList::ShiftLeft, new CardShiftLeft());
	this->cardListByName->emplace(CardList::ShiftRight, new CardShiftRight());
	this->cardListByName->emplace(CardList::Subtraction, new CardSubtraction());
}

CardList::~CardList()
{
	for (auto it = this->cardListByName->begin(); it != this->cardListByName->end(); it++)
	{
		delete(it->second);
	}

	delete(this->cardListByName);
}
