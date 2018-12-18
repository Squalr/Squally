#include "HexusOpponentMara.h"

const std::string HexusOpponentMara::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MARA";
HexusOpponentMara* HexusOpponentMara::instance = nullptr;

HexusOpponentMara* HexusOpponentMara::getInstance()
{
	if (HexusOpponentMara::instance == nullptr)
	{
		HexusOpponentMara::instance = new HexusOpponentMara();
	}

	return HexusOpponentMara::instance;
}

HexusOpponentMara::HexusOpponentMara() : HexusOpponentData(
	EntityResources::Npcs_Mara_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentMara::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.90f),
	HexusOpponentData::generateDeck(25, 0.90f,
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

HexusOpponentMara::~HexusOpponentMara()
{
}
