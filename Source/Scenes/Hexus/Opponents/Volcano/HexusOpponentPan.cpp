#include "HexusOpponentPan.h"

const std::string HexusOpponentPan::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PAN";
HexusOpponentPan* HexusOpponentPan::instance = nullptr;

HexusOpponentPan* HexusOpponentPan::getInstance()
{
	if (HexusOpponentPan::instance == nullptr)
	{
		HexusOpponentPan::instance = new HexusOpponentPan();
	}

	return HexusOpponentPan::instance;
}

HexusOpponentPan::HexusOpponentPan() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Volcano_Npcs_Pan_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	1.0f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentPan::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.78f),
	HexusOpponentData::generateDeck(25, 0.78f,
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

HexusOpponentPan::~HexusOpponentPan()
{
}
