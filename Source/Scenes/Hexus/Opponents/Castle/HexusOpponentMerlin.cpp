#include "HexusOpponentMerlin.h"

const std::string HexusOpponentMerlin::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MERLIN";
HexusOpponentMerlin* HexusOpponentMerlin::instance = nullptr;

HexusOpponentMerlin* HexusOpponentMerlin::getInstance()
{
	if (HexusOpponentMerlin::instance == nullptr)
	{
		HexusOpponentMerlin::instance = new HexusOpponentMerlin();
	}

	return HexusOpponentMerlin::instance;
}

HexusOpponentMerlin::HexusOpponentMerlin() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Castle_Npcs_Merlin_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-48.0f, -80.0f),
	Vec2(-32.0f, -64.0f),
	HexusOpponentMerlin::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Shadow,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
	},
	HexusOpponentData::generateDeck(25, 0.6f,
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

HexusOpponentMerlin::~HexusOpponentMerlin()
{
}
