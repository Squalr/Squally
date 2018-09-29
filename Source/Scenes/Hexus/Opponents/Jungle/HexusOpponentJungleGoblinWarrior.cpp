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
	Vec2(16.0f, -96.0f),
	HexusOpponentJungleGoblinWarrior::StringKeyOpponentName,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Subtraction),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary8),
	},
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary3),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary5),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary6),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary7),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal6),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal7),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex5),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex6),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex7),
		CardList::getInstance()->cardListByName->at(CardKeys::Flip2),
		CardList::getInstance()->cardListByName->at(CardKeys::Flip3),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	})
{
}

HexusOpponentJungleGoblinWarrior::~HexusOpponentJungleGoblinWarrior()
{
}
