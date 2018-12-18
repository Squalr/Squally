#include "HexusOpponentAnubisWarrior.h"

const std::string HexusOpponentAnubisWarrior::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ANUBIS_WARRIOR";
HexusOpponentAnubisWarrior* HexusOpponentAnubisWarrior::instance = nullptr;

HexusOpponentAnubisWarrior* HexusOpponentAnubisWarrior::getInstance()
{
	if (HexusOpponentAnubisWarrior::instance == nullptr)
	{
		HexusOpponentAnubisWarrior::instance = new HexusOpponentAnubisWarrior();
	}

	return HexusOpponentAnubisWarrior::instance;
}

HexusOpponentAnubisWarrior::HexusOpponentAnubisWarrior() : HexusOpponentData(
	EntityResources::Enemies_AnubisWarrior_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-32.0f, -64.0f),
	HexusOpponentAnubisWarrior::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.29f),
	HexusOpponentData::generateDeck(25, 0.29f,
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

HexusOpponentAnubisWarrior::~HexusOpponentAnubisWarrior()
{
}
