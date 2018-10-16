#include "HexusOpponentYsara.h"

const std::string HexusOpponentYsara::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_YSARA";
HexusOpponentYsara* HexusOpponentYsara::instance = nullptr;

HexusOpponentYsara* HexusOpponentYsara::getInstance()
{
	if (HexusOpponentYsara::instance == nullptr)
	{
		HexusOpponentYsara::instance = new HexusOpponentYsara();
	}

	return HexusOpponentYsara::instance;
}

HexusOpponentYsara::HexusOpponentYsara() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Mech_Npcs_Ysara_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -16.0f),
	HexusOpponentYsara::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.93f,
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

HexusOpponentYsara::~HexusOpponentYsara()
{
}
