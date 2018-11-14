#include "HexusOpponentIgneus.h"

const std::string HexusOpponentIgneus::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_IGNEUS";
HexusOpponentIgneus* HexusOpponentIgneus::instance = nullptr;

HexusOpponentIgneus* HexusOpponentIgneus::getInstance()
{
	if (HexusOpponentIgneus::instance == nullptr)
	{
		HexusOpponentIgneus::instance = new HexusOpponentIgneus();
	}

	return HexusOpponentIgneus::instance;
}

HexusOpponentIgneus::HexusOpponentIgneus() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Volcano_Npcs_Igneus_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	1.0f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentIgneus::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.75f),
	HexusOpponentData::generateDeck(25, 0.75f,
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

HexusOpponentIgneus::~HexusOpponentIgneus()
{
}
