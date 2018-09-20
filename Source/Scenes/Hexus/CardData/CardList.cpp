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

/*
	this->cardListByName->emplace(CardList::Binary0, new Binary0());
	this->cardListByName->emplace(CardList::Binary1, new Binary1());
	this->cardListByName->emplace(CardList::Binary2, new Binary2());
	this->cardListByName->emplace(CardList::Binary3, new Binary3());
	this->cardListByName->emplace(CardList::Binary4, new Binary4());
	this->cardListByName->emplace(CardList::Binary5, new Binary5());
	this->cardListByName->emplace(CardList::Binary6, new Binary6());
	this->cardListByName->emplace(CardList::Binary7, new Binary7());
	this->cardListByName->emplace(CardList::Binary8, new Binary8());
	this->cardListByName->emplace(CardList::Binary9, new Binary9());
	this->cardListByName->emplace(CardList::Binary10, new Binary10());
	this->cardListByName->emplace(CardList::Binary11, new Binary11());
	this->cardListByName->emplace(CardList::Binary12, new Binary12());
	this->cardListByName->emplace(CardList::Binary13, new Binary13());
	this->cardListByName->emplace(CardList::Binary14, new Binary14());
	this->cardListByName->emplace(CardList::Binary15, new Binary15());
	this->cardListByName->emplace(CardList::Binary15, new Binary15());

	this->cardListByName->emplace(CardList::Decimal0, new Decimal0());
	this->cardListByName->emplace(CardList::Decimal1, new Decimal1());
	this->cardListByName->emplace(CardList::Decimal2, new Decimal2());
	this->cardListByName->emplace(CardList::Decimal3, new Decimal3());
	this->cardListByName->emplace(CardList::Decimal4, new Decimal4());
	this->cardListByName->emplace(CardList::Decimal5, new Decimal5());
	this->cardListByName->emplace(CardList::Decimal6, new Decimal6());
	this->cardListByName->emplace(CardList::Decimal7, new Decimal7());
	this->cardListByName->emplace(CardList::Decimal8, new Decimal8());
	this->cardListByName->emplace(CardList::Decimal9, new Decimal9());
	this->cardListByName->emplace(CardList::Decimal10, new Decimal10());
	this->cardListByName->emplace(CardList::Decimal11, new Decimal11());
	this->cardListByName->emplace(CardList::Decimal12, new Decimal12());
	this->cardListByName->emplace(CardList::Decimal13, new Decimal13());
	this->cardListByName->emplace(CardList::Decimal14, new Decimal14());
	this->cardListByName->emplace(CardList::Decimal15, new Decimal15());

	this->cardListByName->emplace(CardList::Hex0, new Hex0());
	this->cardListByName->emplace(CardList::Hex1, new Hex1());
	this->cardListByName->emplace(CardList::Hex2, new Hex2());
	this->cardListByName->emplace(CardList::Hex3, new Hex3());
	this->cardListByName->emplace(CardList::Hex4, new Hex4());
	this->cardListByName->emplace(CardList::Hex5, new Hex5());
	this->cardListByName->emplace(CardList::Hex6, new Hex6());
	this->cardListByName->emplace(CardList::Hex7, new Hex7());
	this->cardListByName->emplace(CardList::Hex8, new Hex8());
	this->cardListByName->emplace(CardList::Hex9, new Hex9());
	this->cardListByName->emplace(CardList::Hex10, new Hex10());
	this->cardListByName->emplace(CardList::Hex11, new Hex11());
	this->cardListByName->emplace(CardList::Hex12, new Hex12());
	this->cardListByName->emplace(CardList::Hex13, new Hex13());
	this->cardListByName->emplace(CardList::Hex14, new Hex14());
	this->cardListByName->emplace(CardList::Hex15, new Hex15());

	this->cardListByName->emplace(CardList::Addition, new Addition());
	this->cardListByName->emplace(CardList::Flip1, new Flip1());
	this->cardListByName->emplace(CardList::Flip2, new Flip2());
	this->cardListByName->emplace(CardList::Flip3, new Flip3());
	this->cardListByName->emplace(CardList::Flip4, new Flip4());
	this->cardListByName->emplace(CardList::Inverse, new Inverse());
	this->cardListByName->emplace(CardList::LogicalAnd, new LogicalAnd());
	this->cardListByName->emplace(CardList::LogicalOr, new LogicalOr());
	this->cardListByName->emplace(CardList::LogicalXor, new LogicalXor());
	this->cardListByName->emplace(CardList::ShiftLeft, new ShiftLeft());
	this->cardListByName->emplace(CardList::ShiftRight, new ShiftRight());
	this->cardListByName->emplace(CardList::Subtraction, new Subtraction());
	*/
}

CardList::~CardList()
{
	for (auto it = this->cardListByName->begin(); it != this->cardListByName->end(); it++)
	{
		delete(it->second);
	}

	delete(this->cardListByName);
}
