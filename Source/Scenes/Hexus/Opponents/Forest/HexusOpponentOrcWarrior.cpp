#include "HexusOpponentOrcWarrior.h"

const std::string HexusOpponentOrcWarrior::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ORC_WARRIOR";
HexusOpponentOrcWarrior* HexusOpponentOrcWarrior::instance = nullptr;

HexusOpponentOrcWarrior* HexusOpponentOrcWarrior::getInstance()
{
	if (HexusOpponentOrcWarrior::instance == nullptr)
	{
		HexusOpponentOrcWarrior::instance = new HexusOpponentOrcWarrior();
	}

	return HexusOpponentOrcWarrior::instance;
}

HexusOpponentOrcWarrior::HexusOpponentOrcWarrior() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Forest_Enemies_OrcWarrior_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -48.0f),
	Vec2(-48.0f, -48.0f),
	HexusOpponentOrcWarrior::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0, 7, 0.33f, 0.33f,
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

HexusOpponentOrcWarrior::~HexusOpponentOrcWarrior()
{
}
