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
	EntityResources::Enemies_LexiconCrypts_Gargoyle_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-32.0f, -80.0f),
	HexusOpponentGargoyle::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.895f),
	HexusOpponentData::generateDeck(25, 0.895f,
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
