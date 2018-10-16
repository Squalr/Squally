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
	Resources::Entities_Platformer_Environment_Castle_Enemies_Zombie_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-32.0f, -32.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentZombie::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Shadow,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
	},
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

HexusOpponentZombie::~HexusOpponentZombie()
{
}
