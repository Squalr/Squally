#include "HexusOpponentGarin.h"

const std::string HexusOpponentGarin::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GARIN";
HexusOpponentGarin* HexusOpponentGarin::instance = nullptr;

HexusOpponentGarin* HexusOpponentGarin::getInstance()
{
	if (HexusOpponentGarin::instance == nullptr)
	{
		HexusOpponentGarin::instance = new HexusOpponentGarin();
	}

	return HexusOpponentGarin::instance;
}

HexusOpponentGarin::HexusOpponentGarin() : HexusOpponentData(
	EntityResources::Platformer_Environment_Castle_Npcs_Garin_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	0.85f,
	Vec2(-32.0f, -64.0f),
	Vec2(-32.0f, -48.0f),
	HexusOpponentGarin::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.5f),
	HexusOpponentData::generateDeck(25, 0.5f,
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

HexusOpponentGarin::~HexusOpponentGarin()
{
}
