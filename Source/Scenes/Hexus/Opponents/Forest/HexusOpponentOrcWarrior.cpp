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
	EntityResources::Enemies_EndianForest_OrcWarrior_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -48.0f),
	Vec2(-48.0f, -48.0f),
	HexusOpponentOrcWarrior::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.335f),
	HexusOpponentData::generateDeck(25, 0.335f,
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
