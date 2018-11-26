#include "HexusOpponentVoidArcher.h"

const std::string HexusOpponentVoidArcher::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_VOID_ARCHER";
HexusOpponentVoidArcher* HexusOpponentVoidArcher::instance = nullptr;

HexusOpponentVoidArcher* HexusOpponentVoidArcher::getInstance()
{
	if (HexusOpponentVoidArcher::instance == nullptr)
	{
		HexusOpponentVoidArcher::instance = new HexusOpponentVoidArcher();
	}

	return HexusOpponentVoidArcher::instance;
}

HexusOpponentVoidArcher::HexusOpponentVoidArcher() : HexusOpponentData(
	EntityResources::Platformer_Environment_Obelisk_Enemies_VoidArcher_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -40.0f),
	HexusOpponentVoidArcher::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.855f),
	HexusOpponentData::generateDeck(25, 0.855f,
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

HexusOpponentVoidArcher::~HexusOpponentVoidArcher()
{
}
