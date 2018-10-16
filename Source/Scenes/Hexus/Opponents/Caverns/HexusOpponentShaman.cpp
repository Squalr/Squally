#include "HexusOpponentShaman.h"

const std::string HexusOpponentShaman::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SHAMAN";
HexusOpponentShaman* HexusOpponentShaman::instance = nullptr;

HexusOpponentShaman* HexusOpponentShaman::getInstance()
{
	if (HexusOpponentShaman::instance == nullptr)
	{
		HexusOpponentShaman::instance = new HexusOpponentShaman();
	}

	return HexusOpponentShaman::instance;
}

HexusOpponentShaman::HexusOpponentShaman() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Caverns_Enemies_Shaman_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	0.7f,
	Vec2(-32.0f, -32.0f),
	Vec2(-16.0f, -16.0f),
	HexusOpponentShaman::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Shadow,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
	},
	HexusOpponentData::generateDeck(25, 0.405f,
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalXor),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentShaman::~HexusOpponentShaman()
{
}
