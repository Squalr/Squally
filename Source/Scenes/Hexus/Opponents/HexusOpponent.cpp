#pragma init_seg(".CRT$XCU-030")
#include "HexusOpponent.h"

const std::string HexusOpponent::Kickstarter00 = "Name me";
const std::string HexusOpponent::Kickstarter01 = "Name me 2";
const std::string HexusOpponent::Kickstarter02 = "Name me 3";
const std::string HexusOpponent::Kickstarter03 = "Name me 4";
const std::string HexusOpponent::Kickstarter04 = "Name me 5";
const std::string HexusOpponent::Kickstarter05 = "Name me 6";
const std::string HexusOpponent::Kickstarter06 = "Name me 7";
const std::string HexusOpponent::Kickstarter07 = "Name me 8";
const std::string HexusOpponent::Kickstarter08 = "Name me 9";
const std::string HexusOpponent::Kickstarter09 = "Name me 10";
const std::string HexusOpponent::Kickstarter010 = "Name me 11";
const std::string HexusOpponent::Kickstarter011 = "Name me 12";
const std::string HexusOpponent::Kickstarter012 = "Name me 13";
const std::string HexusOpponent::Kickstarter013 = "Name me 14";
const std::string HexusOpponent::Kickstarter014 = "Name me 15";
const std::string HexusOpponent::Kickstarter015 = "Metal Golem";
const std::string HexusOpponent::BossKrampus = "Krampus";

std::map<std::string, HexusOpponent*> HexusOpponent::cardListByName = {
	{ HexusOpponent::Kickstarter00, new HexusOpponent(Resources::Entities_Platformer_Npcs_EgyptianMummy_Animations, HexusOpponent::Kickstarter00) },
	{ HexusOpponent::Kickstarter01, new HexusOpponent(Resources::Entities_Platformer_Npcs_EgyptianMummy_Animations, HexusOpponent::Kickstarter01) },
	{ HexusOpponent::Kickstarter02, new HexusOpponent(Resources::Entities_Platformer_Npcs_EgyptianMummy_Animations, HexusOpponent::Kickstarter02) },
	{ HexusOpponent::Kickstarter03, new HexusOpponent(Resources::Entities_Platformer_Npcs_EgyptianMummy_Animations, HexusOpponent::Kickstarter03) },
	{ HexusOpponent::Kickstarter04, new HexusOpponent(Resources::Entities_Platformer_Npcs_EgyptianMummy_Animations, HexusOpponent::Kickstarter04) },
	{ HexusOpponent::Kickstarter05, new HexusOpponent(Resources::Entities_Platformer_Npcs_EgyptianMummy_Animations, HexusOpponent::Kickstarter05) },
	{ HexusOpponent::Kickstarter06, new HexusOpponent(Resources::Entities_Platformer_Npcs_EgyptianMummy_Animations, HexusOpponent::Kickstarter06) },
	{ HexusOpponent::Kickstarter07, new HexusOpponent(Resources::Entities_Platformer_Npcs_EgyptianMummy_Animations, HexusOpponent::Kickstarter07) },
	{ HexusOpponent::Kickstarter08, new HexusOpponent(Resources::Entities_Platformer_Npcs_EgyptianMummy_Animations, HexusOpponent::Kickstarter08) },
	{ HexusOpponent::Kickstarter09, new HexusOpponent(Resources::Entities_Platformer_Npcs_EgyptianMummy_Animations, HexusOpponent::Kickstarter09) },
	{ HexusOpponent::Kickstarter010, new HexusOpponent(Resources::Entities_Platformer_Npcs_EgyptianMummy_Animations, HexusOpponent::Kickstarter010) },
	{ HexusOpponent::Kickstarter011, new HexusOpponent(Resources::Entities_Platformer_Npcs_EgyptianMummy_Animations, HexusOpponent::Kickstarter011) },
	{ HexusOpponent::Kickstarter012, new HexusOpponent(Resources::Entities_Platformer_Npcs_EgyptianMummy_Animations, HexusOpponent::Kickstarter012) },
	{ HexusOpponent::Kickstarter013, new HexusOpponent(Resources::Entities_Platformer_Npcs_EgyptianMummy_Animations, HexusOpponent::Kickstarter013) },
	{ HexusOpponent::Kickstarter014, new HexusOpponent(Resources::Entities_Platformer_Npcs_EgyptianMummy_Animations, HexusOpponent::Kickstarter014) },
	{ HexusOpponent::Kickstarter015, new HexusOpponent(Resources::Entities_Platformer_Npcs_EgyptianMummy_Animations, HexusOpponent::Kickstarter015) },
	{ HexusOpponent::BossKrampus, new HexusOpponent(Resources::Entities_Platformer_Environment_Caverns_BossKrampus_Animations, HexusOpponent::BossKrampus, CardType::Decimal, 0) },
};

// Use a map here instead of an array. This allows us to remove cards without fucking up the ids of other cards.
// ie) The case of putting out a steam patch to remove a broken card without ruining existing save files.

std::map<int, HexusOpponent*> HexusOpponent::cardListById = {
	{ 0, HexusOpponent::cardListByName.at(HexusOpponent::Kickstarter00) },
	{ 1, HexusOpponent::cardListByName.at(HexusOpponent::Kickstarter01) },
	{ 2, HexusOpponent::cardListByName.at(HexusOpponent::Kickstarter02) },
	{ 2, HexusOpponent::cardListByName.at(HexusOpponent::Kickstarter03) },
	{ 3, HexusOpponent::cardListByName.at(HexusOpponent::Kickstarter04) },
	{ 4, HexusOpponent::cardListByName.at(HexusOpponent::Kickstarter05) },
	{ 5, HexusOpponent::cardListByName.at(HexusOpponent::Kickstarter06) },
	{ 6, HexusOpponent::cardListByName.at(HexusOpponent::Kickstarter07) },
	{ 7, HexusOpponent::cardListByName.at(HexusOpponent::Kickstarter08) },
	{ 8, HexusOpponent::cardListByName.at(HexusOpponent::Kickstarter09) },
	{ 9, HexusOpponent::cardListByName.at(HexusOpponent::Kickstarter010) },
	{ 10, HexusOpponent::cardListByName.at(HexusOpponent::Kickstarter011) },
	{ 11, HexusOpponent::cardListByName.at(HexusOpponent::Kickstarter012) },
	{ 12, HexusOpponent::cardListByName.at(HexusOpponent::Kickstarter013) },
	{ 13, HexusOpponent::cardListByName.at(HexusOpponent::Kickstarter014) },
	{ 14, HexusOpponent::cardListByName.at(HexusOpponent::Kickstarter015) },
	{ 15, HexusOpponent::cardListByName.at(HexusOpponent::BossSanta) },
};

HexusOpponent::HexusOpponent(std::string newCardResourceFile, std::string newCardName, CardType newCardType, unsigned int newAttack)
{
	this->cardResourceFile = newCardResourceFile;
	this->cardName = newCardName;
	this->cardType = newCardType;
	this->attack = newAttack;
}

HexusOpponent::~HexusOpponent()
{
}

std::string HexusOpponent::getCardTypeString()
{
	switch (this->cardType)
	{
	case HexusOpponent::CardType::Binary:
		return "BIN";
	case HexusOpponent::CardType::Decimal:
		return "DEC";
	case HexusOpponent::CardType::Hexidecimal:
		return "HEX";
	case HexusOpponent::CardType::Special_AND:
		return "AND";
	case HexusOpponent::CardType::Special_OR:
		return "OR";
	case HexusOpponent::CardType::Special_XOR:
		return "XOR";
	case HexusOpponent::CardType::Special_SHL:
		return "SHL";
	case HexusOpponent::CardType::Special_SHR:
		return "SHR";
	case HexusOpponent::CardType::Special_INV:
		return "INV";
	case HexusOpponent::CardType::Special_FLIP1:
		return "FLIP1";
	case HexusOpponent::CardType::Special_FLIP2:
		return "FLIP2";
	case HexusOpponent::CardType::Special_FLIP3:
		return "FLIP3";
	case HexusOpponent::CardType::Special_FLIP4:
		return "FLIP4";
	case HexusOpponent::CardType::Special_ADD:
		return "ADD";
	case HexusOpponent::CardType::Special_SUB:
		return "SUB";
	}
}
