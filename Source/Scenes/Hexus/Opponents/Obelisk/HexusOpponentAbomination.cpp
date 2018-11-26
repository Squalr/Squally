#include "HexusOpponentAbomination.h"

const std::string HexusOpponentAbomination::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ABOMINATION";
HexusOpponentAbomination* HexusOpponentAbomination::instance = nullptr;

HexusOpponentAbomination* HexusOpponentAbomination::getInstance()
{
	if (HexusOpponentAbomination::instance == nullptr)
	{
		HexusOpponentAbomination::instance = new HexusOpponentAbomination();
	}

	return HexusOpponentAbomination::instance;
}

HexusOpponentAbomination::HexusOpponentAbomination() : HexusOpponentData(
	EntityResources::Platformer_Environment_Obelisk_Enemies_Abomination_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	0.7f,
	Vec2(-48.0f, -64.0f),
	Vec2(-48.0f, -48.0f),
	HexusOpponentAbomination::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.815f),
	HexusOpponentData::generateDeck(25, 0.815f,
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

HexusOpponentAbomination::~HexusOpponentAbomination()
{
}
