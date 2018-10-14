#include "HexusOpponentAnubisPup.h"

const std::string HexusOpponentAnubisPup::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ANUBIS_PUP";
HexusOpponentAnubisPup* HexusOpponentAnubisPup::instance = nullptr;

HexusOpponentAnubisPup* HexusOpponentAnubisPup::getInstance()
{
	if (HexusOpponentAnubisPup::instance == nullptr)
	{
		HexusOpponentAnubisPup::instance = new HexusOpponentAnubisPup();
	}

	return HexusOpponentAnubisPup::instance;
}

HexusOpponentAnubisPup::HexusOpponentAnubisPup() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Ruins_Enemies_AnubisPup_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentAnubisPup::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0, 6, 0.33f, 0.33f,
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

HexusOpponentAnubisPup::~HexusOpponentAnubisPup()
{
}
