#include "HexusOpponentMummyWarrior.h"

const std::string HexusOpponentMummyWarrior::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MUMMY_WARRIOR";
HexusOpponentMummyWarrior* HexusOpponentMummyWarrior::instance = nullptr;

HexusOpponentMummyWarrior* HexusOpponentMummyWarrior::getInstance()
{
	if (HexusOpponentMummyWarrior::instance == nullptr)
	{
		HexusOpponentMummyWarrior::instance = new HexusOpponentMummyWarrior();
	}

	return HexusOpponentMummyWarrior::instance;
}

HexusOpponentMummyWarrior::HexusOpponentMummyWarrior() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Ruins_Enemies_MummyWarrior_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	0.85f,
	Vec2(-32.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentMummyWarrior::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.265f),
	HexusOpponentData::generateDeck(25, 0.265f,
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

HexusOpponentMummyWarrior::~HexusOpponentMummyWarrior()
{
}
