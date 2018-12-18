#include "HexusOpponentDemonGhost.h"

const std::string HexusOpponentDemonGhost::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_GHOST";
HexusOpponentDemonGhost* HexusOpponentDemonGhost::instance = nullptr;

HexusOpponentDemonGhost* HexusOpponentDemonGhost::getInstance()
{
	if (HexusOpponentDemonGhost::instance == nullptr)
	{
		HexusOpponentDemonGhost::instance = new HexusOpponentDemonGhost();
	}

	return HexusOpponentDemonGhost::instance;
}

HexusOpponentDemonGhost::HexusOpponentDemonGhost() : HexusOpponentData(
	EntityResources::Enemies_DaemonsHallow_DemonGhost_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -16.0f),
	HexusOpponentDemonGhost::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.715f),
	HexusOpponentData::generateDeck(25, 0.715f,
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

HexusOpponentDemonGhost::~HexusOpponentDemonGhost()
{
}
