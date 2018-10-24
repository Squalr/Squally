#include "HexusOpponentCindra.h"

const std::string HexusOpponentCindra::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CINDRA";
HexusOpponentCindra* HexusOpponentCindra::instance = nullptr;

HexusOpponentCindra* HexusOpponentCindra::getInstance()
{
	if (HexusOpponentCindra::instance == nullptr)
	{
		HexusOpponentCindra::instance = new HexusOpponentCindra();
	}

	return HexusOpponentCindra::instance;
}

HexusOpponentCindra::HexusOpponentCindra() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Volcano_Npcs_Cindra_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentCindra::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.74f),
	HexusOpponentData::generateDeck(25, 0.74f,
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

HexusOpponentCindra::~HexusOpponentCindra()
{
}
