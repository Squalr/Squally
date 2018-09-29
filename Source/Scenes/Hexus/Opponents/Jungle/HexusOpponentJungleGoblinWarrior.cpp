#include "HexusOpponentJungleGoblinWarrior.h"

const std::string HexusOpponentJungleGoblinWarrior::StringKeyOpponentName = "Squally_Npc_Names_Jungle_Goblin_Warrior";
HexusOpponentJungleGoblinWarrior* HexusOpponentJungleGoblinWarrior::instance = nullptr;

HexusOpponentJungleGoblinWarrior* HexusOpponentJungleGoblinWarrior::getInstance()
{
	if (HexusOpponentJungleGoblinWarrior::instance == nullptr)
	{
		HexusOpponentJungleGoblinWarrior::instance = new HexusOpponentJungleGoblinWarrior();
	}

	return HexusOpponentJungleGoblinWarrior::instance;
}

HexusOpponentJungleGoblinWarrior::HexusOpponentJungleGoblinWarrior() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Enemies_GoblinWarrior_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	0.4f,
	Vec2(48.0f, -144.0f),
	Vec2(0.0f, 0.0f),
	HexusOpponentJungleGoblinWarrior::StringKeyOpponentName,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
	},
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary1),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex1),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex2),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex2),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::Subtraction),
		CardList::getInstance()->cardListByName->at(CardKeys::Subtraction),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	})
{
}

HexusOpponentJungleGoblinWarrior::~HexusOpponentJungleGoblinWarrior()
{
}
