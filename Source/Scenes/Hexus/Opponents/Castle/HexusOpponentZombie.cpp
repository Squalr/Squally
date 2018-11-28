#include "HexusOpponentZombie.h"

const std::string HexusOpponentZombie::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ZOMBIE";
HexusOpponentZombie* HexusOpponentZombie::instance = nullptr;

HexusOpponentZombie* HexusOpponentZombie::getInstance()
{
	if (HexusOpponentZombie::instance == nullptr)
	{
		HexusOpponentZombie::instance = new HexusOpponentZombie();
	}

	return HexusOpponentZombie::instance;
}

HexusOpponentZombie::HexusOpponentZombie() : HexusOpponentData(
	EntityResources::Environment_Castle_Enemies_Zombie_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-32.0f, -32.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentZombie::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.515f),
	HexusOpponentData::generateDeck(25, 0.515f,
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

HexusOpponentZombie::~HexusOpponentZombie()
{
}
