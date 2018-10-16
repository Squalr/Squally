#include "HexusOpponentMara.h"

const std::string HexusOpponentMara::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MARA";
HexusOpponentMara* HexusOpponentMara::instance = nullptr;

HexusOpponentMara* HexusOpponentMara::getInstance()
{
	if (HexusOpponentMara::instance == nullptr)
	{
		HexusOpponentMara::instance = new HexusOpponentMara();
	}

	return HexusOpponentMara::instance;
}

HexusOpponentMara::HexusOpponentMara() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Mech_Npcs_Mara_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentMara::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.90f,
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

HexusOpponentMara::~HexusOpponentMara()
{
}
