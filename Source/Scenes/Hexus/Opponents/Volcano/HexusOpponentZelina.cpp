#include "HexusOpponentZelina.h"

const std::string HexusOpponentZelina::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ZELINA";
HexusOpponentZelina* HexusOpponentZelina::instance = nullptr;

HexusOpponentZelina* HexusOpponentZelina::getInstance()
{
	if (HexusOpponentZelina::instance == nullptr)
	{
		HexusOpponentZelina::instance = new HexusOpponentZelina();
	}

	return HexusOpponentZelina::instance;
}

HexusOpponentZelina::HexusOpponentZelina() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Volcano_Npcs_Zelina_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	1.0f,
	Vec2(-48.0f, -72.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentZelina::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.71f,
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

HexusOpponentZelina::~HexusOpponentZelina()
{
}
