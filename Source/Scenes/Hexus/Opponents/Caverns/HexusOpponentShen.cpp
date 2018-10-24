#include "HexusOpponentShen.h"

const std::string HexusOpponentShen::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SHEN";
HexusOpponentShen* HexusOpponentShen::instance = nullptr;

HexusOpponentShen* HexusOpponentShen::getInstance()
{
	if (HexusOpponentShen::instance == nullptr)
	{
		HexusOpponentShen::instance = new HexusOpponentShen();
	}

	return HexusOpponentShen::instance;
}

HexusOpponentShen::HexusOpponentShen() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Caverns_Npcs_Shen_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	1.0f,
	Vec2(-32.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentShen::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.49f),
	HexusOpponentData::generateDeck(25, 0.49f,
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

HexusOpponentShen::~HexusOpponentShen()
{
}
