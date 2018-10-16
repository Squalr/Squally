#include "HexusOpponentYeti.h"

const std::string HexusOpponentYeti::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_YETI";
HexusOpponentYeti* HexusOpponentYeti::instance = nullptr;

HexusOpponentYeti* HexusOpponentYeti::getInstance()
{
	if (HexusOpponentYeti::instance == nullptr)
	{
		HexusOpponentYeti::instance = new HexusOpponentYeti();
	}

	return HexusOpponentYeti::instance;
}

HexusOpponentYeti::HexusOpponentYeti() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Snow_Enemies_Yeti_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.5f,
	Vec2(-48.0f, -72.0f),
	Vec2(-32.0f, -56.0f),
	HexusOpponentYeti::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.61f,
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

HexusOpponentYeti::~HexusOpponentYeti()
{
}
