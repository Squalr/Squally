#include "HexusOpponentMechGolemDark.h"

const std::string HexusOpponentMechGolemDark::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MECH_GOLEM_DARK";
HexusOpponentMechGolemDark* HexusOpponentMechGolemDark::instance = nullptr;

HexusOpponentMechGolemDark* HexusOpponentMechGolemDark::getInstance()
{
	if (HexusOpponentMechGolemDark::instance == nullptr)
	{
		HexusOpponentMechGolemDark::instance = new HexusOpponentMechGolemDark();
	}

	return HexusOpponentMechGolemDark::instance;
}

HexusOpponentMechGolemDark::HexusOpponentMechGolemDark() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Mech_Enemies_MechGolemDark_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	0.5f,
	Vec2(-48.0f, -144.0f),
	Vec2(-48.0f, -144.0f),
	HexusOpponentMechGolemDark::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.945f,
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

HexusOpponentMechGolemDark::~HexusOpponentMechGolemDark()
{
}
