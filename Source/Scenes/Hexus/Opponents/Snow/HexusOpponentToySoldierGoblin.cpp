#include "HexusOpponentToySoldierGoblin.h"

const std::string HexusOpponentToySoldierGoblin::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TOY_SOLDIER_GOBLIN";
HexusOpponentToySoldierGoblin* HexusOpponentToySoldierGoblin::instance = nullptr;

HexusOpponentToySoldierGoblin* HexusOpponentToySoldierGoblin::getInstance()
{
	if (HexusOpponentToySoldierGoblin::instance == nullptr)
	{
		HexusOpponentToySoldierGoblin::instance = new HexusOpponentToySoldierGoblin();
	}

	return HexusOpponentToySoldierGoblin::instance;
}

HexusOpponentToySoldierGoblin::HexusOpponentToySoldierGoblin() : HexusOpponentData(
	EntityResources::Environment_Snow_Enemies_ToySoldierGoblin_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -16.0f),
	HexusOpponentToySoldierGoblin::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.6f),
	HexusOpponentData::generateDeck(25, 0.6f,
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

HexusOpponentToySoldierGoblin::~HexusOpponentToySoldierGoblin()
{
}
