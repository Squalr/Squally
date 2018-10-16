#include "HexusOpponentGargoyle.h"

const std::string HexusOpponentGargoyle::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GARGOYLE";
HexusOpponentGargoyle* HexusOpponentGargoyle::instance = nullptr;

HexusOpponentGargoyle* HexusOpponentGargoyle::getInstance()
{
	if (HexusOpponentGargoyle::instance == nullptr)
	{
		HexusOpponentGargoyle::instance = new HexusOpponentGargoyle();
	}

	return HexusOpponentGargoyle::instance;
}

HexusOpponentGargoyle::HexusOpponentGargoyle() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Obelisk_Enemies_Gargoyle_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-32.0f, -80.0f),
	HexusOpponentGargoyle::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.8f,
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

HexusOpponentGargoyle::~HexusOpponentGargoyle()
{
}
