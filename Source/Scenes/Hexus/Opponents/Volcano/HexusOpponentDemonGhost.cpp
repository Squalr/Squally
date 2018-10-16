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
	Resources::Entities_Platformer_Environment_Volcano_Enemies_DemonGhost_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -16.0f),
	HexusOpponentDemonGhost::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
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
