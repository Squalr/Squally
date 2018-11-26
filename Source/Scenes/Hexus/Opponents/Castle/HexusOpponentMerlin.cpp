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
	EntityResources::Platformer_Environment_Castle_Npcs_Merlin_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-48.0f, -80.0f),
	Vec2(-32.0f, -64.0f),
	HexusOpponentMerlin::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.57f),
	HexusOpponentData::generateDeck(25, 0.57f,
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
